#include <avr/wdt.h>
#include <SPI.h>
#include <Ethernet.h>
#include "EthWebServer.h"
#include "Parameters.h"
#include "printp.h"

const uint8_t defMAC[6] PROGMEM = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const uint32_t defIP = 0xF001A8C0; // 192.168.1.240
const uint32_t defMask = 0x00FFFFFF; // 255.255.255.0
const uint32_t defGate = 0x0101A8C0; // 192.168.1.1
const uint32_t defDNS = 0x0101A8C0; // 192.168.1.1

const char pathData[] PROGMEM = "/data";
const char pathStore[] PROGMEM = "/store";
const char pathEthernet[] PROGMEM = "/ethernet";
const char pathRestart[] PROGMEM = "/restart";

const char paramReboot[] PROGMEM = "reboot";
const char paramMAC[] PROGMEM = "mac";
const char paramIP[] PROGMEM = "ip";
const char paramMask[] PROGMEM = "mask";
const char paramGate[] PROGMEM = "gate";
const char paramDNS[] PROGMEM = "dns";

const char jsonUptime[] PROGMEM = "uptime";

class EthernetParameters : public EEPROMParameters {
public:
  EthernetParameters() : EEPROMParameters(2) {}
  bool setParameter(const char* name, const char* value);

  uint8_t mac[6];
  uint32_t ip;
  uint32_t mask;
  uint32_t gate;
  uint32_t dns;

protected:
  int16_t readData(uint16_t offset, uint8_t chunk);
  int16_t writeData(uint16_t offset, uint8_t chunk);
  void defaults(uint8_t chunk);
};

EthernetParameters params;

class WebServer : public EthWebServer {
public:
  WebServer(uint16_t port = 80) : EthWebServer(port) {}

protected:
  void handleRequest(const char* uri);
  void handleRootPage(const char* uri);
  void handleData(const char* uri);
  void handleStore(const char* uri);
  void handleEthernet(const char* uri);
  void handleRestart(const char* uri);

private:
  void printIP(PGM_P label, PGM_P name, uint32_t ip, PGM_P extra = NULL);
};

static void softReset() {
  Serial.println(F("Rebooting..."));
  Serial.flush();

  wdt_enable(WDTO_15MS);
//  while (true);
}

/***
 * EthernetParameters class implementation
 */

static uint8_t strToHex(const char* digits) {
  uint8_t result;

  if ((digits[0] >= '0') && (digits[0] <= '9'))
    result = (digits[0] - '0') << 4;
  else if ((digits[0] >= 'A') && (digits[0] <= 'F'))
    result = (digits[0] - 'A' + 10) << 4;
  else if ((digits[0] >= 'a') && (digits[0] <= 'f'))
    result = (digits[0] - 'a' + 10) << 4;
  else
    return 0;

  if ((digits[1] >= '0') && (digits[1] <= '9'))
    result |= (digits[1] - '0');
  else if ((digits[1] >= 'A') && (digits[1] <= 'F'))
    result |= (digits[1] - 'A' + 10);
  else if ((digits[1] >= 'a') && (digits[1] <= 'f'))
    result |= (digits[1] - 'a' + 10);
  else
    return 0;

  return result;
}

bool EthernetParameters::setParameter(const char* name, const char* value) {
  if (! strcmp_P(name, paramMAC)) {
    if (strlen(value) == 12) {
      for (uint8_t i = 0; i < 6; ++i)
        params.mac[i] = strToHex(&value[i * 2]);
    }
  } else if (! strcmp_P(name, paramIP)) {
    params.ip = atol(value);
  } else if (! strcmp_P(name, paramMask)) {
    params.mask = atol(value);
  } else if (! strcmp_P(name, paramGate)) {
    params.gate = atol(value);
  } else if (! strcmp_P(name, paramDNS)) {
    params.dns = atol(value);
  } else
    return EEPROMParameters::setParameter(name, value);

  return true;
}

int16_t EthernetParameters::readData(uint16_t offset, uint8_t chunk) {
  int16_t result = offset;

  if (chunk == 0) {
    result += _read(result, mac, sizeof(mac));
  } else if (chunk == 1) {
    result += _read(result, &ip, sizeof(ip));
    result += _read(result, &mask, sizeof(mask));
    result += _read(result, &gate, sizeof(gate));
    result += _read(result, &dns, sizeof(dns));
  } else
    result = -1;

  return result;
}

int16_t EthernetParameters::writeData(uint16_t offset, uint8_t chunk) {
  int16_t result = offset;

  if (chunk == 0) {
    result += _write(result, mac, sizeof(mac));
  } else if (chunk == 1) {
    result += _write(result, &ip, sizeof(ip));
    result += _write(result, &mask, sizeof(mask));
    result += _write(result, &gate, sizeof(gate));
    result += _write(result, &dns, sizeof(dns));
  } else
    result = -1;

  return result;
}

void EthernetParameters::defaults(uint8_t chunk) {
  if (chunk == 0) {
    memcpy_P(mac, defMAC, sizeof(mac));
  }
  if (chunk <= 1) {
    ip = 0; // defIP;
    mask = defMask;
    gate = defGate;
    dns = defDNS;
  }
}

/***
 * WebServer class implementation
 */

void WebServer::handleRequest(const char* uri) {
  if (! strcmp_P(uri, pathData))
    handleData(uri);
  else if (! strcmp_P(uri, pathStore))
    handleStore(uri);
  else if (! strcmp_P(uri, pathEthernet))
    handleEthernet(uri);
  else if (! strcmp_P(uri, pathRestart))
    handleRestart(uri);
  else
    EthWebServer::handleRequest(uri);
}

void WebServer::handleRootPage(const char* uri) {
  static const char codePattern[] PROGMEM = "document.getElementById('%0').innerHTML=data.%0;\n";

  if (! startResponse_P(200, typeTextHtml))
    return;
  htmlPageStart_P(PSTR("Arduino Web Server"));
  htmlPageStdStyle();
  htmlPageStyle_P(PSTR("table{\n\
border-collapse:collapse;\n\
}\n\
table,th,td{\n\
border:1px solid black;\n\
text-align:center;\n\
}"));
  htmlPageStdScript();
  htmlPageScriptStart();

  uint8_t i;
  PGM_P substs[] = { pathData };

  printsubst_P(*_client, PSTR("function refreshData(){\n\
var request=getXmlHttpRequest();\n\
request.open('GET','%0?dummy='+Date.now(),true);\n\
request.onreadystatechange=function(){\n\
if (request.readyState==4){\n\
var data=JSON.parse(request.responseText);\n"), substs);
  substs[0] = jsonUptime;
  printsubst_P(*_client, codePattern, substs);
  for (i = 2; i <= 19; ++i) {
    if ((i == 4) || ((i >= 10) && (i <= 13))) // Ignore SD and SPI pins
      continue;
/*
    _client->print(F("document.getElementById('"));
*/
    print_P(*_client, codePattern, 25); // "document.getElementById('"
    if (i < 14) {
      _client->write('D');
      _client->print(i);
    } else {
      _client->write('A');
      _client->print(i - 14);
    }
/*
    _client->print(F("').innerHTML=data."));
*/
    print_P(*_client, &codePattern[27], 18); // "').innerHTML=data."
    if (i < 14) {
      _client->write('D');
      _client->print(i);
    } else {
      _client->write('A');
      _client->print(i - 14);
    }
    _client->print(F(";\n"));
  }
  _client->print(F("}\n\
}\n\
request.send(null);\n\
}\n\
setInterval(refreshData,500);\n"));
  htmlPageScriptEnd();
  htmlPageBody_P();
  htmlTag_P(tagH3, NULL, PSTR("Arduino Web Server"), true);
  printsubst_P(*_client, PSTR("Uptime: <span id=\"%0\">?</span> sec.\n"), substs);
  htmlTag_P(tagP, NULL, NULL, true);
  htmlTagStart_P(tagTable);
  htmlTag_P(tagCaption, NULL, PSTR("Arduino pins"), true);
  htmlTagStart_P(tagTR);
  htmlTag_P(tagTH, NULL, PSTR("Pin #"));
  htmlTag_P(tagTH, NULL, PSTR("Value"));
  htmlTagEnd_P(tagTR, true);
  for (i = 2; i <= 19; ++i) {
    if ((i == 4) || ((i >= 10) && (i <= 13))) // Ignore SD and SPI pins
      continue;
    htmlTagStart_P(tagTR);
    htmlTagStart_P(tagTD);
    if (i < 14) {
      _client->print(i);
    } else {
      _client->write('A');
      _client->print(i - 14);
    }
    htmlTagEnd_P(tagTD);
    htmlTagStart_P(tagTD);
    _client->print(F("<span id=\""));
    if (i < 14) {
      _client->write('D');
      _client->print(i);
    } else {
      _client->write('A');
      _client->print(i - 14);
    }
    _client->print(F("\">?</span>"));
    htmlTagEnd_P(tagTD);
    htmlTagEnd_P(tagTR, true);
  }
  htmlTagEnd_P(tagTable, true);
  htmlTag_P(tagP, NULL, NULL, true);
  htmlTagInput_P(inputTypeButton, NULL, PSTR("Ethernet Setup"), PSTR("onclick=\"location.href='/ethernet'\""), true);
  htmlTagInput_P(inputTypeButton, NULL, PSTR("Reboot"), PSTR("onclick=\"if(confirm('Are you sure to reboot?')) location.href='/restart'\""), true);
  htmlPageEnd();
  endResponse();
}

void WebServer::handleData(const char* uri) {
  if (! startResponse_P(200, typeTextJson))
    return;
  _client->write('{');
  _client->write(charQuote);
  print_P(*_client, jsonUptime);
  _client->write(charQuote);
  _client->write(charColon);
  _client->print(millis() / 1000);
  for (uint8_t i = 2; i <= 19; ++i) {
    if ((i == 4) || ((i >= 10) && (i <= 13))) // Ignore SD and SPI pins
      continue;
    _client->write(charComma);
    _client->write(charQuote);
    if (i < 14) {
      _client->write('D');
      _client->print(i);
    } else {
      _client->write('A');
      _client->print(i - 14);
    }
    _client->write(charQuote);
    _client->write(charColon);
    if (i < 14) {
      _client->print(digitalRead(i));
    } else {
      _client->print(analogRead(i));
    }
  }
  _client->write('}');
  endResponse();
}

void WebServer::handleStore(const char* uri) {
  for (uint8_t i = 0; i < args(); ++i) {
    params.setParameter(argName(i), arg(i));
  }
  if (! params.write()) {
    Serial.println(F("Error writing config to EEPROM!"));
  } else {
    Serial.println(F("Config succefully stored to EEPROM"));
  }

  if (! startResponse_P(200, typeTextHtml))
    return;
  htmlPageStart_P(PSTR("Store Config"));
  _client->print(F("<meta http-equiv=\"refresh\" content=\"5;URL=/\">\n"));
  htmlPageStdStyle();
  htmlPageBody_P();
  _client->print(F("Configuration stored successfully.</br>\n"));
  if (*arg_P(paramReboot) == '1') {
    _client->print(F("<i>You must reboot module to apply new configuration!</i>\n"));
  }
  _client->print(F("<p>\n\
Wait for 5 sec. or click <a href=\"/\">this</a> to return to main page.\n"));
  htmlPageEnd();
  endResponse();
}

static void printHex(Stream& stream, uint8_t data) {
  uint8_t digit;

  digit = data / 16;
  stream.write(digit < 10 ? '0' + digit : 'A' + digit - 10);
  digit = data % 16;
  stream.write(digit < 10 ? '0' + digit : 'A' + digit - 10);
}

void WebServer::printIP(PGM_P label, PGM_P name, uint32_t ip, PGM_P extra) {
  static const char codePattern[] PROGMEM = "\" size=\"%0\" maxlength=\"%0\" onblur=\"checkNumber(this,0,255)\"/>";

  PGM_P substs[] = { PSTR("3") };

  htmlTag_P(tagLabel, NULL, label);
  htmlTagBR(true);
  for (uint8_t i = 0; i < 4; ++i) {
/*
    _client->print(F("<input type=\""));
    print_P(*_client, inputTypeText);
    _client->print(F("\" name=\""));
    print_P(*_client, paramIP);
*/
    _client->write(charLess);
    print_P(*_client, tagInput);
    _client->write(charSpace);
    print_P(*_client, attrType);
    print_P(*_client, inputTypeText);
    _client->write(charQuote);
    _client->write(charSpace);
    print_P(*_client, attrName);
    print_P(*_client, name);
    _client->print(i);
/*
    _client->print(F("\" value=\""));
*/
    _client->write(charQuote);
    _client->write(charSpace);
    print_P(*_client, attrValue);
    _client->print((ip >> (i * 8)) & 0xFF);
/*
    _client->print(F("\" size=\"3\" maxlength=\"3\" onblur=\"checkNumber(this,0,255)\"/>"));
*/
    printsubst_P(*_client, codePattern, substs);
    if (i < 3)
      _client->print(F(" .\n"));
  }
  if (extra)
    print_P(*_client, extra);
  htmlTagBR(true);
  htmlTagInput_P(inputTypeHidden, name, strEmpty, NULL, true);
}

void WebServer::handleEthernet(const char* uri) {
  static const char codePattern1[] PROGMEM = "form.%0.value=form.%00.value|(form.%01.value<<8)|(form.%02.value<<16)|(form.%03.value<<24);\n";
  static const char codePattern2[] PROGMEM = ".disabled=true;";
  static const char codePattern3[] PROGMEM = "\" size=\"2\" maxlength=\"2\" onblur=\"checkMAC(this)\"/>";

  uint8_t i;

  if (! startResponse_P(200, typeTextHtml))
    return;
  htmlPageStart_P(PSTR("Ethernet Setup"));
  htmlPageStdStyle();
  htmlPageScriptStart();
/*
  _client->print(F("function completeForm(form){\n\
form."));
  print_P(*_client, paramMAC);
  _client->print(F(".value="));
*/
  PGM_P substs[] = { paramMAC };

  printsubst_P(*_client, PSTR("function completeForm(form){\n\
form.%0.value="), substs);
  for (i = 0; i < 6; ++i) {
    if (i)
      _client->write('+');
/*
    _client->print(F("form."));
    print_P(*_client, paramMAC);
*/
    printsubst_P(*_client, codePattern1, substs, 7);
    _client->print(i);
    _client->print(F(".value"));
  }
/*
  _client->print(F(";\n\
form."));
  print_P(*_client, paramIP);
  _client->print(F(".value=form."));
  print_P(*_client, paramIP);
  _client->print(F("0.value|(form."));
  print_P(*_client, paramIP);
  _client->print(F("1.value<<8)|(form."));
  print_P(*_client, paramIP);
  _client->print(F("2.value<<16)|(form."));
  print_P(*_client, paramIP);
  _client->print(F("3.value<<24);\n\
form."));
  print_P(*_client, paramMask);
  _client->print(F(".value=form."));
  print_P(*_client, paramMask);
  _client->print(F("0.value|(form."));
  print_P(*_client, paramMask);
  _client->print(F("1.value<<8)|(form."));
  print_P(*_client, paramMask);
  _client->print(F("2.value<<16)|(form."));
  print_P(*_client, paramMask);
  _client->print(F("3.value<<24);\n\
form."));
  print_P(*_client, paramGate);
  _client->print(F(".value=form."));
  print_P(*_client, paramGate);
  _client->print(F("0.value|(form."));
  print_P(*_client, paramGate);
  _client->print(F("1.value<<8)|(form."));
  print_P(*_client, paramGate);
  _client->print(F("2.value<<16)|(form."));
  print_P(*_client, paramGate);
  _client->print(F("3.value<<24);\n\
form."));
  print_P(*_client, paramDNS);
  _client->print(F(".value=form."));
  print_P(*_client, paramDNS);
  _client->print(F("0.value|(form."));
  print_P(*_client, paramDNS);
  _client->print(F("1.value<<8)|(form."));
  print_P(*_client, paramDNS);
  _client->print(F("2.value<<16)|(form."));
  print_P(*_client, paramDNS);
  _client->print(F("3.value<<24);\n"));
*/
  _client->print(F(";\n"));
  substs[0] = paramIP;
  printsubst_P(*_client, codePattern1, substs);
  substs[0] = paramMask;
  printsubst_P(*_client, codePattern1, substs);
  substs[0] = paramGate;
  printsubst_P(*_client, codePattern1, substs);
  substs[0] = paramDNS;
  printsubst_P(*_client, codePattern1, substs);
  substs[0] = paramMAC;
  for (i = 0; i < 6; ++i) {
/*
    _client->print(F("form."));
    print_P(*_client, paramMAC);
*/
    printsubst_P(*_client, codePattern1, substs, 7);
    _client->print(i);
/*
    _client->print(F(".disabled=true;"));
*/
    print_P(*_client, codePattern2);
  }
  _client->write(charLF);
  substs[0] = paramIP;
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("form."));
    print_P(*_client, paramIP);
*/
    printsubst_P(*_client, codePattern1, substs, 7);
    _client->print(i);
/*
    _client->print(F(".disabled=true;"));
*/
    print_P(*_client, codePattern2);
  }
  _client->write(charLF);
  substs[0] = paramMask;
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("form."));
    print_P(*_client, paramMask);
*/
    printsubst_P(*_client, codePattern1, substs, 7);
    _client->print(i);
/*
    _client->print(F(".disabled=true;"));
*/
    print_P(*_client, codePattern2);
  }
  _client->write(charLF);
  substs[0] = paramGate;
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("form."));
    print_P(*_client, paramGate);
*/
    printsubst_P(*_client, codePattern1, substs, 7);
    _client->print(i);
/*
    _client->print(F(".disabled=true;"));
*/
    print_P(*_client, codePattern2);
  }
  _client->write(charLF);
  substs[0] = paramDNS;
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("form."));
    print_P(*_client, paramDNS);
*/
    printsubst_P(*_client, codePattern1, substs, 7);
    _client->print(i);
/*
    _client->print(F(".disabled=true;"));
*/
    print_P(*_client, codePattern2);
  }
  _client->print(F("\n}\n\
function checkMAC(src){\n\
var value = src.value;\n\
value=value.toUpperCase();\n\
if(value.length == 2){\n\
if((value.charAt(0)<'0')||((value.charAt(0)>'9')&&((value.charAt(0)<'A')||(value.charAt(0)>'F'))))\n\
value='0'+value.charAt(1);\n\
if((value.charAt(1)<'0')||((value.charAt(1)>'9')&&((value.charAt(1)<'A')||(value.charAt(1)>'F'))))\n\
value=value.charAt(0)+'0';\n\
}else\n\
value=\"00\";\n\
src.value=value;\n\
}\n\
function checkNumber(src,minval,maxval){\n\
var value=parseInt(src.value);\n\
if(isNaN(value))\n\
value=minval;\n\
if(value<minval)\n\
value=minval;\n\
if(value>maxval)\n\
value=maxval;\n\
src.value=value.toString();\n\
}\n"));
  htmlPageScriptEnd();
  htmlPageBody_P();
/*
  _client->print(F("<form name=\"ethernet\" action=\""));
  print_P(*_client, pathStore);
  _client->print(F("\" method=\"GET\" onsubmit=\"completeForm(this)\">\n"));
*/
  substs[0] = pathStore;
  printsubst_P(*_client, PSTR("<form name=\"ethernet\" action=\"%0\" method=\"GET\" onsubmit=\"completeForm(this)\">\n"), substs);
  htmlTag_P(tagH3, NULL, PSTR("Ethernet Setup"), true);
  htmlTag_P(tagLabel, NULL, PSTR("MAC address:"));
  htmlTagBR(true);
  for (i = 0; i < 6; ++i) {
/*
    _client->print(F("<input type=\""));
    print_P(*_client, inputTypeText);
    _client->print(F("\" name=\""));
    print_P(*_client, paramMAC);
*/
    _client->write(charLess);
    print_P(*_client, tagInput);
    _client->write(charSpace);
    print_P(*_client, attrType);
    print_P(*_client, inputTypeText);
    _client->write(charQuote);
    _client->write(charSpace);
    print_P(*_client, attrName);
    print_P(*_client, paramMAC);
    _client->print(i);
/*
    _client->print(F("\" value=\""));
*/
    _client->write(charQuote);
    _client->write(charSpace);
    print_P(*_client, attrValue);
    printHex(*_client, params.mac[i]);
/*
    _client->print(F("\" size=\"2\" maxlength=\"2\" onblur=\"checkMAC(this)\"/>"));
*/
    print_P(*_client, codePattern3);
    if (i < 5)
      _client->print(F(" :\n"));
  }
  htmlTagBR(true);
  htmlTagInput_P(inputTypeHidden, paramMAC, strEmpty, NULL, true);
/*
  htmlTag_P(tagLabel, NULL, PSTR("IP address:"));
  htmlTagBR(true);
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("<input type=\""));
    print_P(*_client, inputTypeText);
    _client->print(F("\" name=\""));
    print_P(*_client, paramIP);
* /
    substs[0] = inputTypeText;
    printsubst_P(*_client, codePattern3, substs);
    substs[0] = paramIP;
    printsubst_P(*_client, codePattern4, substs);
    _client->print(i);
/*
    _client->print(F("\" value=\""));
* /
    print_P(*_client, codePattern5);
    _client->print((params.ip >> (i * 8)) & 0xFF);
/*
    _client->print(F("\" size=\"3\" maxlength=\"3\" onblur=\"checkNumber(this,0,255)\"/>"));
* /
    substs[0] = PSTR("3");
    printsubst_P(*_client, codePattern6, substs);
    print_P(*_client, codePattern8);
    if (i < 3)
      _client->print(F(" .\n"));
  }
  _client->print(F("\n(0.0.0.0 for DHCP)"));
  htmlTagBR(true);
  htmlTagInput_P(inputTypeHidden, paramIP, strEmpty, NULL, true);
*/
  printIP(PSTR("IP address:"), paramIP, params.ip, PSTR("\n(0.0.0.0 for DHCP)"));
/*
  htmlTag_P(tagLabel, NULL, PSTR("Submet mask:"));
  htmlTagBR(true);
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("<input type=\""));
    print_P(*_client, inputTypeText);
    _client->print(F("\" name=\""));
    print_P(*_client, paramMask);
* /
    substs[0] = inputTypeText;
    printsubst_P(*_client, codePattern3, substs);
    substs[0] = paramMask;
    printsubst_P(*_client, codePattern4, substs);
    _client->print(i);
/*
    _client->print(F("\" value=\""));
* /
    print_P(*_client, codePattern5);
    _client->print((params.mask >> (i * 8)) & 0xFF);
/*
    _client->print(F("\" size=\"3\" maxlength=\"3\" onblur=\"checkNumber(this,0,255)\"/>"));
* /
    substs[0] = PSTR("3");
    printsubst_P(*_client, codePattern6, substs);
    print_P(*_client, codePattern8);
    if (i < 3)
      _client->print(F(" .\n"));
  }
  htmlTagBR(true);
  htmlTagInput_P(inputTypeHidden, paramMask, strEmpty, NULL, true);
*/
  printIP(PSTR("Submet mask:"), paramMask, params.mask);
/*
  htmlTag_P(tagLabel, NULL, PSTR("Gateway address:"));
  htmlTagBR(true);
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("<input type=\""));
    print_P(*_client, inputTypeText);
    _client->print(F("\" name=\""));
    print_P(*_client, paramGate);
* /
    substs[0] = inputTypeText;
    printsubst_P(*_client, codePattern3, substs);
    substs[0] = paramGate;
    printsubst_P(*_client, codePattern4, substs);
    _client->print(i);
/*
    _client->print(F("\" value=\""));
* /
    print_P(*_client, codePattern5);
    _client->print((params.gate >> (i * 8)) & 0xFF);
/*
    _client->print(F("\" size=\"3\" maxlength=\"3\" onblur=\"checkNumber(this,0,255)\"/>"));
* /
    substs[0] = PSTR("3");
    printsubst_P(*_client, codePattern6, substs);
    print_P(*_client, codePattern8);
    if (i < 3)
      _client->print(F(" .\n"));
  }
  htmlTagBR(true);
  htmlTagInput_P(inputTypeHidden, paramGate, strEmpty, NULL, true);
*/
  printIP(PSTR("Gateway address:"), paramGate, params.gate);
/*
  htmlTag_P(tagLabel, NULL, PSTR("DNS address:"));
  htmlTagBR(true);
  for (i = 0; i < 4; ++i) {
/*
    _client->print(F("<input type=\""));
    print_P(*_client, inputTypeText);
    _client->print(F("\" name=\""));
    print_P(*_client, paramDNS);
* /
    substs[0] = inputTypeText;
    printsubst_P(*_client, codePattern3, substs);
    substs[0] = paramDNS;
    printsubst_P(*_client, codePattern4, substs);
    _client->print(i);
/*
    _client->print(F("\" value=\""));
* /
    print_P(*_client, codePattern5);
    _client->print((params.dns >> (i * 8)) & 0xFF);
/*
    _client->print(F("\" size=\"3\" maxlength=\"3\" onblur=\"checkNumber(this,0,255)\"/>"));
* /
    substs[0] = PSTR("3");
    printsubst_P(*_client, codePattern6, substs);
    print_P(*_client, codePattern8);
    if (i < 3)
      _client->print(F(" .\n"));
  }
  htmlTagBR(true);
  htmlTagInput_P(inputTypeHidden, paramDNS, strEmpty, NULL, true);
*/
  printIP(PSTR("DNS address:"), paramDNS, params.dns);
  htmlTagInput_P(inputTypeHidden, paramReboot, PSTR("1"), NULL, true);
  htmlTag_P(tagP, NULL, NULL, true);
  htmlTagInput_P(inputTypeSubmit, NULL, PSTR("Save"), NULL, true);
  htmlTagInput_P(inputTypeButton, NULL, PSTR("Back"), PSTR("onclick=\"location.href='/'\""), true);
  _client->print(F("</form>\n"));
  htmlPageEnd();
  endResponse();
}

void WebServer::handleRestart(const char* uri) {
  if (! startResponse_P(200, typeTextHtml))
    return;
  htmlPageStart_P(PSTR("Reboot"));
  htmlPageStdStyle();
  _client->print(F("<meta http-equiv=\"refresh\" content=\"5;URL=/\">\n"));
  htmlPageBody_P();
  _client->print(F("Rebooting...\n"));
  htmlPageEnd();
  endResponse();

  softReset();
}

const uint32_t MAINTENANCE_PERIOD = 28800000; // 8 hours in ms.
const uint32_t MAINTENANCE_RETRY = 60000; // 1 min. in ms.

WebServer www(80);
uint32_t nextMaintenance;

void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH); // Inactivate SD card

  Serial.begin(115200);
  SPI.begin();

  if (! params.begin()) {
    Serial.println(F("Error initialization of EEPROM!"));
  }
  if (! params.read()) {
    Serial.println(F("EEPROM is empty or corrupt, default parameters will be used!"));
  }
  nextMaintenance = (uint32_t)-1;
  if (params.ip) {
    Ethernet.begin(params.mac, IPAddress(params.ip), IPAddress(params.dns), IPAddress(params.gate), IPAddress(params.mask));
    Serial.print(F("Use static IP "));
  } else {
    if (Ethernet.begin(params.mac)) {
      Serial.print(F("Use DHCP IP "));
      nextMaintenance = millis() + MAINTENANCE_PERIOD;
    } else {
      Serial.println(F("Failed to configure Ethernet using DHCP!"));
      Ethernet.begin(params.mac, IPAddress(defIP));
      Serial.print(F("Use default static IP "));
    }
  }
  Serial.print(Ethernet.localIP());
  Serial.print('/');
  Serial.print(Ethernet.subnetMask());
  Serial.print(F(", gateway "));
  Serial.print(Ethernet.gatewayIP());
  Serial.print(F(" and DNS server "));
  Serial.println(Ethernet.dnsServerIP());

  www.begin();
}

void loop() {
  if ((nextMaintenance != (uint32_t)-1) && (millis() >= nextMaintenance)) {
    switch (Ethernet.maintain()) {
      case DHCP_CHECK_RENEW_FAIL:
      case DHCP_CHECK_REBIND_FAIL:
        Serial.println(F("Error renewing or rebinding DHCP address!"));
        nextMaintenance = millis() + MAINTENANCE_RETRY;
        break;
      case DHCP_CHECK_RENEW_OK:
      case DHCP_CHECK_REBIND_OK:
        Serial.print(F("Renewed or rebinded DHCP address "));
        Serial.println(Ethernet.localIP());
      default: // no break before is not an error!
        nextMaintenance = millis() + MAINTENANCE_PERIOD;
    }
  }

  www.handleClient();

  delay(1);
}
