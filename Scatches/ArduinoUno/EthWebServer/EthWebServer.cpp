#include <stdlib.h>
#include <string.h>
#include "EthWebServer.h"
#include "printp.h"

EthWebServer::EthWebServer(uint16_t port) : _server(new EthernetServer(port)), _client(NULL), _bufferLength(0), _uri(NULL), _argCount(0), _headerCount(0) {}

EthWebServer::~EthWebServer() {
  clearHeaders();
  clearArgs();
  if (_client)
    delete _client;
  if (_server)
    delete _server;
}

void EthWebServer::begin() {
  _server->begin();
}

void EthWebServer::handleClient() {
  EthernetClient client = _server->available();
  if ((! client) || (! client.connected()))
    return;

  _client = &client;

  if (parseRequest()) {
    handleRequest(_uri);
  }

  _client = NULL;
}

bool EthWebServer::checkClient() {
  bool result = (_client && _client->connected());
#ifndef NDEBUG
  if (! result)
    println_P(Serial, strClientNotConnected);
#endif
  return result;
}

static void _startResponse(Stream& stream, int16_t code, const char* contentType, int16_t contentLength, bool progmem) {
  stream.print(F("HTTP/1.1 "));
  stream.print(code);
  stream.write(charSpace);
  println_P(stream, EthWebServer::responseCodeToString(code));
  stream.print(F("Content-Type: "));
  if (progmem)
    println_P(stream, contentType);
  else
    stream.println(contentType);
  if (contentLength != -1) {
    stream.print(F("Content-Length: "));
    stream.println(contentLength);
  }
  stream.println(F("Connection: close"));
  stream.println(F("Access-Control-Allow-Origin: *"));
  stream.println();
}

bool EthWebServer::startResponse(int16_t code, const char* contentType, int16_t contentLength) {
  if (! checkClient())
    return false;

  _startResponse(*_client, code, contentType, contentLength, false);

  return true;
}

bool EthWebServer::startResponse_P(int16_t code, PGM_P contentType, int16_t contentLength) {
  if (! checkClient())
    return false;

  _startResponse(*_client, code, contentType, contentLength, true);

  return true;
}

bool EthWebServer::endResponse() {
  if (! checkClient())
    return false;

  _client->flush();
  _client->stop();

  return true;
}

void EthWebServer::handleRequest(const char* uri) {
  if ((! strcmp_P(uri, strSlash)) || (! strcmp_P(uri, pathRoot)) || ((! strncmp_P(uri, pathRoot, 10)) && (! uri[10])))
    handleRootPage(uri);
  else if (! strcmp_P(uri, pathStdStyle))
    handleStdStyle(uri);
  else if (! strcmp_P(uri, pathStdScript))
    handleStdScript(uri);
  else
    handleNotFound(uri);
}

void EthWebServer::handleNotFound(const char* uri) {
  if (! startResponse_P(404, typeTextHtml))
    return;
  htmlPageStart_P(PSTR("Page Not Found"));
  htmlPageStdStyle();
  htmlPageBody_P();
  htmlTag_P(tagH3, NULL, PSTR("Page Not Found!"), true);
  _client->print(F("URL: "));
  _client->print(uri);
  htmlTagBR(true);

#ifndef LIGHT
  uint8_t i;

  _client->print(F("Argument(s) count: "));
  _client->print(args());
  htmlTagBR(true);
  for (i = 0; i < args(); ++i) {
    _client->print(i + 1);
    _client->print(' ');
    _client->print(argName(i));
    _client->print(F("=\""));
    _client->print(arg(i));
    _client->print('"');
    htmlTagBR(true);
  }
  htmlTagBR(true);
  _client->print(F("Header(s) count: "));
  _client->print(headers());
  htmlTagBR(true);
  for (i = 0; i < headers(); ++i) {
    _client->print(i + 1);
    _client->print(' ');
    _client->print(headerName(i));
    _client->print(F(": \""));
    _client->print(header(i));
    _client->print('"');
    htmlTagBR(true);
  }
#endif
  htmlPageEnd();
  endResponse();
}

void EthWebServer::handleStdStyle(const char* uri) {
  static const char style[] PROGMEM = "body{\n\
background-color:rgb(240,240,240);\n\
}";

  send_P(200, typeTextCss, style);
}

void EthWebServer::handleStdScript(const char* uri) {
#ifndef LIGHT
  static const char script[] PROGMEM = "function getXmlHttpRequest(){\n\
var xmlhttp;\n\
try{\n\
xmlhttp=new ActiveXObject(\"Msxml2.XMLHTTP\");\n\
}catch(e){\n\
try{\n\
xmlhttp=new ActiveXObject(\"Microsoft.XMLHTTP\");\n\
}catch(E){\n\
xmlhttp=false;\n\
}\n\
}\n\
if ((!xmlhttp)&&(typeof XMLHttpRequest!='undefined')){\n\
xmlhttp=new XMLHttpRequest();\n\
}\n\
return xmlhttp;\n\
}\n\
function openUrl(url){\n\
var request=getXmlHttpRequest();\n\
request.open(\"GET\",url,false);\n\
request.send(null);\n\
}";
#else
  static const char script[] PROGMEM = "function getXmlHttpRequest(){\n\
var xmlhttp=new XMLHttpRequest();\n\
return xmlhttp;\n\
}\n\
function openUrl(url){\n\
var request=getXmlHttpRequest();\n\
request.open(\"GET\",url,false);\n\
request.send(null);\n\
}";
#endif

  send_P(200, typeApplicationJavascript, script);
}

const char* EthWebServer::arg(const char* name) {
  for (uint8_t i = 0; i < _argCount; ++i) {
    if (! strcmp(_args[i].name, name))
      return _args[i].value;
  }

  return NULL;
}

const char* EthWebServer::arg_P(PGM_P name) {
  for (uint8_t i = 0; i < _argCount; ++i) {
    if (! strcmp_P(_args[i].name, name))
      return _args[i].value;
  }

  return NULL;
}

const char* EthWebServer::arg(uint8_t ind) {
  if (ind < _argCount)
    return _args[ind].value;
  else
    return NULL;
}

const char* EthWebServer::argName(uint8_t ind) {
  if (ind < _argCount)
    return _args[ind].name;
  else
    return NULL;
}

bool EthWebServer::hasArg(const char* name) {
  for (uint8_t i = 0; i < _argCount; ++i) {
    if (! strcmp(_args[i].name, name))
      return true;
  }

  return false;
}

bool EthWebServer::hasArg_P(PGM_P name) {
  for (uint8_t i = 0; i < _argCount; ++i) {
    if (! strcmp_P(_args[i].name, name))
      return true;
  }

  return false;
}

const char* EthWebServer::header(const char* name) {
  for (uint8_t i = 0; i < _headerCount; ++i) {
    if (! strcmp(_headers[i].name, name))
      return _headers[i].value;
  }

  return NULL;
}

const char* EthWebServer::header_P(PGM_P name) {
  for (uint8_t i = 0; i < _headerCount; ++i) {
    if (! strcmp_P(_headers[i].name, name))
      return _headers[i].value;
  }

  return NULL;
}

const char* EthWebServer::header(uint8_t ind) {
  if (ind < _headerCount)
    return _headers[ind].value;
  else
    return NULL;
}

const char* EthWebServer::headerName(uint8_t ind) {
  if (ind < _headerCount)
    return _headers[ind].name;
  else
    return NULL;
}

bool EthWebServer::hasHeader(const char* name) {
  for (uint8_t i = 0; i < _headerCount; ++i) {
    if (! strcmp(_headers[i].name, name))
      return true;
  }

  return false;
}

bool EthWebServer::hasHeader_P(PGM_P name) {
  for (uint8_t i = 0; i < _headerCount; ++i) {
    if (! strcmp_P(_headers[i].name, name))
      return true;
  }

  return false;
}

bool EthWebServer::send(int16_t code, const char* contentType, const char* content) {
  return (startResponse(code, contentType, strlen(content)) && sendContent(content) && endResponse());
}

bool EthWebServer::send_P(int16_t code, PGM_P contentType, PGM_P content) {
  return (startResponse_P(code, contentType, strlen_P(content)) && sendContent_P(content) && endResponse());
}

static void _sendHeader(Stream& stream, const char* name, const char* value, bool progmem) {
  if (progmem)
    print_P(stream, name);
  else
    stream.print(name);
  stream.print(F(": "));
  if (progmem)
    println_P(stream, value);
  else
    stream.println(value);
}

bool EthWebServer::sendHeader(const char* name, const char* value) {
  if (! checkClient())
    return false;

  _sendHeader(*_client, name, value, false);

  return true;
}

bool EthWebServer::sendHeader_P(PGM_P name, PGM_P value) {
  if (! checkClient())
    return false;

  _sendHeader(*_client, name, value, true);

  return true;
}

bool EthWebServer::sendContent(Stream& stream) {
  while (stream.available()) {
    char c = stream.read();
    if (_client->write(c) != sizeof(c))
      return false;
  }

  return true;
}

static bool _sendContent(Stream& stream, const char* content, bool progmem) {
  uint16_t bytesRemain = progmem ? strlen_P(content) : strlen(content);

  while (bytesRemain--) {
    char c;

    if (progmem)
      c = pgm_read_byte(content++);
    else
      c = *content++;
    if (stream.write(c) != sizeof(c))
      return false;
  }

  return true;
}

bool EthWebServer::sendContent(const char* content) {
  if (! checkClient())
    return false;

  return _sendContent(*_client, content, false);
}

bool EthWebServer::sendContent_P(PGM_P content) {
  if (! checkClient())
    return false;

  return _sendContent(*_client, content, true);
}

PGM_P EthWebServer::responseCodeToString(int16_t code) {
  if (code = 100)
    return PSTR("Continue");
  else if (code == 101)
    return PSTR("Switching Protocols");
  else if (code == 200)
    return PSTR("OK");
  else if (code == 201)
    return PSTR("Created");
  else if (code == 202)
    return PSTR("Accepted");
  else if (code == 203)
    return PSTR("Non-Authoritative Information");
  else if (code == 204)
    return PSTR("No Content");
  else if (code == 205)
    return PSTR("Reset Content");
  else if (code == 206)
    return PSTR("Partial Content");
  else if (code == 300)
    return PSTR("Multiple Choices");
  else if (code == 301)
    return PSTR("Moved Permanently");
  else if (code == 302)
    return PSTR("Found");
  else if (code == 303)
    return PSTR("See Other");
  else if (code == 304)
    return PSTR("Not Modified");
  else if (code == 305)
    return PSTR("Use Proxy");
  else if (code == 307)
    return PSTR("Temporary Redirect");
  else if (code == 400)
    return PSTR("Bad Request");
  else if (code == 401)
    return PSTR("Unauthorized");
  else if (code == 402)
    return PSTR("Payment Required");
  else if (code == 403)
    return PSTR("Forbidden");
  else if (code == 404)
    return PSTR("Not Found");
  else if (code == 405)
    return PSTR("Method Not Allowed");
  else if (code == 406)
    return PSTR("Not Acceptable");
  else if (code == 407)
    return PSTR("Proxy Authentication Required");
  else if (code == 408)
    return PSTR("Request Time-out");
  else if (code == 409)
    return PSTR("Conflict");
  else if (code == 410)
    return PSTR("Gone");
  else if (code == 411)
    return PSTR("Length Required");
  else if (code == 412)
    return PSTR("Precondition Failed");
  else if (code == 413)
    return PSTR("Request Entity Too Large");
  else if (code == 414)
    return PSTR("Request-URI Too Large");
  else if (code == 415)
    return PSTR("Unsupported Media Type");
  else if (code == 416)
    return PSTR("Requested range not satisfiable");
  else if (code == 417)
    return PSTR("Expectation Failed");
  else if (code == 500)
    return PSTR("Internal Server Error");
  else if (code == 501)
    return PSTR("Not Implemented");
  else if (code == 502)
    return PSTR("Bad Gateway");
  else if (code == 503)
    return PSTR("Service Unavailable");
  else if (code == 504)
    return PSTR("Gateway Time-out");
  else if (code == 505)
    return PSTR("HTTP Version not supported");
  else
    return strEmpty;
}

static uint8_t hex(const char* digits) {
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

char* EthWebServer::urlDecode(char* decoded, const char* url) {
  char* result = decoded;
  int16_t len = strlen(url);

  for (int16_t i = 0; i < len; ++i) {
    if ((url[i] == charPercent) && (i + 2 < len)) {
      *decoded++ = hex(&url[++i]);
      ++i;
    } else if (url[i] == charPlus)
      *decoded++ = charSpace;
    else
      *decoded++ = url[i];
  }
  *decoded = charNull;

  return result;
}

static uint16_t readUntil(EthernetClient* client, char* buf, uint16_t maxlen, char delimiter) {
  uint16_t result = 0;

  if (client->connected() && maxlen) {
    while (client->available()) {
      char c = client->read();
      buf[result++] = c;
      if ((result >= maxlen) || (c == delimiter))
        break;
    }
  }

  return result;
}

static bool skipUntil(EthernetClient* client, uint16_t maxlen, char delimiter) {
  if (client->connected() && maxlen) {
    while (client->available()) {
      char c = client->read();
      if (c == delimiter) {
        return true;
      }
      if (! --maxlen)
        break;
    }
  }

  return false;
}

bool EthWebServer::parseRequest() {
  _uri = NULL;
  clearHeaders();
  clearArgs();
  _bufferLength = readUntil(_client, (char*)_buffer, BUFFER_SIZE, charCR);
  if ((_bufferLength <= 1) || (! skipUntil(_client, 1, charLF)))
    return false;
  if (strncmp_P((const char*)_buffer, PSTR("GET "), 4) || strncmp_P((const char*)&_buffer[_bufferLength - 10], PSTR(" HTTP/1.1"), 9)) { // HTTP request first line looks like "GET /path HTTP/1.1"
#ifndef NDEBUG
    println_P(Serial, strBadRequest);
#endif
    return false;
  }
  _uri = (char*)&_buffer[4];
  _buffer[_bufferLength - 10] = charNull;
  _bufferLength -= 9;
  char* argList = strchr(_uri, charQuestion);
  if (argList) {
    *argList++ = charNull;
    parseArguments(argList);
  }
  char* headerList = NULL;
  uint16_t bufRemain = BUFFER_SIZE - _bufferLength;
  while (bufRemain) {
    uint16_t numRead = readUntil(_client, (char*)&_buffer[_bufferLength], bufRemain, charCR);
    if ((numRead <= 1) || (! skipUntil(_client, 1, charLF)))
      break;
    _buffer[_bufferLength + numRead - 1] = charNull;
    if (! strchr((const char*)&_buffer[_bufferLength], charColon))
      break;
    if (! headerList)
      headerList = (char*)&_buffer[_bufferLength];
    _bufferLength += numRead;
    bufRemain -= numRead;
  }
  _client->flush();
  if (headerList)
    parseHeaders(headerList);

  return true;
}

bool EthWebServer::parseArguments(const char* argList) {
  uint8_t cnt = 0;
  char* str = (char*)argList;

  while (*str) {
    if (*str++ == charEqual)
      ++cnt;
  }
  if (! cnt)
    return false;
  _args = (pair_t*)malloc(sizeof(pair_t) * cnt);
  if (! _args) {
#ifndef NDEBUG
    println_P(Serial, strNotEnoughMemory);
#endif
    return false;
  }
  str = (char*)argList;
  _args[0].name = str;
  _args[0].value = NULL;
  _argCount = 0;
  while (*str) {
    if (*str == charEqual) {
      *str++ = charNull;
      if (! strlen(_args[_argCount].name)) {
        clearArgs();
        return false;
      }
      _args[_argCount].value = str;
    } else if (*str == charAmpersand) {
      *str++ = charNull;
      if (_args[_argCount].value)
        urlDecode(_args[_argCount].value, _args[_argCount].value);
      if ((! _args[_argCount].value) || (++_argCount >= cnt)) {
        clearArgs();
        return false;
      }
      _args[_argCount].name = str;
      _args[_argCount].value = NULL;
    } else
      ++str;
  }
  if ((! strlen(_args[_argCount].name)) || (! _args[_argCount].value) || (++_argCount != cnt)) {
    clearArgs();
    return false;
  }

  return true;
}

bool EthWebServer::parseHeaders(const char* headerList) {
  uint8_t cnt = 0;
  char* str = (char*)headerList;

  while (str < (char*)&_buffer[_bufferLength - 1]) {
    if (*str++ == charColon) {
      ++cnt;
      while (*str++);
    }
  }
  if (! cnt)
    return false;
  _headers = (pair_t*)malloc(sizeof(pair_t) * cnt);
  if (! _headers) {
#ifndef NDEBUG
    println_P(Serial, strNotEnoughMemory);
#endif
    return false;
  }
  str = (char*)headerList;
  _headers[0].name = str;
  _headers[0].value = NULL;
  _headerCount = 0;
  while (str < (char*)&_buffer[_bufferLength - 1]) {
    if (*str == charColon) {
      *str++ = charNull;
      if (! strlen(_headers[_headerCount].name)) {
        clearHeaders();
        return false;
      }
      if (*str == charSpace)
        ++str;
      _headers[_headerCount].value = str;
      while (*str)
        ++str;
    } else if (! *str) {
      if ((! _headers[_headerCount].value) || (++_headerCount >= cnt)) {
        clearHeaders();
        return false;
      }
      _headers[_headerCount].name = ++str;
      _headers[_headerCount].value = NULL;
    } else
      ++str;
  }
  if ((! strlen(_headers[_headerCount].name)) || (! _headers[_headerCount].value) || (++_headerCount != cnt)) {
    clearHeaders();
    return false;
  }

  return true;
}

void EthWebServer::clearArgs() {
  if (_argCount) {
    free((void*)_args);
    _argCount = 0;
  }
}

void EthWebServer::clearHeaders() {
  if (_headerCount) {
    free((void*)_headers);
    _headerCount = 0;
  }
}

static void _htmlTagStart(Stream& stream, const char* type, const char* attrs, bool newline, bool progmem) {
  stream.write(charLess);
  if (progmem)
    print_P(stream, type);
  else
    stream.print(type);
  if (attrs) {
    stream.write(charSpace);
    if (progmem)
      print_P(stream, attrs);
    else
      stream.print(attrs);
  }
  stream.write(charGreater);
  if (newline)
    stream.write(charLF);
}

void EthWebServer::htmlTagStart(const char* type, const char* attrs, bool newline) {
  _htmlTagStart(*_client, type, attrs, newline, false);
}

void EthWebServer::htmlTagStart_P(PGM_P type, PGM_P attrs, bool newline) {
  _htmlTagStart(*_client, type, attrs, newline, true);
}

static void _htmlTagEnd(Stream& stream, const char* type, bool newline, bool progmem) {
  stream.write(charLess);
  stream.write(charSlash);
  if (progmem)
    print_P(stream, type);
  else
    stream.print(type);
  stream.write(charGreater);
  if (newline)
    stream.write(charLF);
}

void EthWebServer::htmlTagEnd(const char* type, bool newline) {
  _htmlTagEnd(*_client, type, newline, false);
}

void EthWebServer::htmlTagEnd_P(PGM_P type, bool newline) {
  _htmlTagEnd(*_client, type, newline, true);
}

static void _htmlPageStart(Stream& stream, const char* title, bool progmem) {
  stream.print(F("<!DOCTYPE "));
  print_P(stream, tagHtml);
  stream.write(charGreater);
  stream.write(charLF);
  _htmlTagStart(stream, tagHtml, NULL, true, true);
  _htmlTagStart(stream, tagHead, NULL, true, true);
  _htmlTagStart(stream, tagTitle, NULL, false, true);
  if (progmem)
    print_P(stream, title);
  else
    stream.print(title);
  _htmlTagEnd(stream, tagTitle, true, true);
}

void EthWebServer::htmlPageStart(const char* title) {
  _htmlPageStart(*_client, title, false);
}

void EthWebServer::htmlPageStart_P(PGM_P title) {
  _htmlPageStart(*_client, title, true);
}

static void _htmlPageStyleStart(Stream& stream) {
  stream.write(charLess);
  print_P(stream, tagStyle);
  stream.write(charSpace);
  print_P(stream, attrType);
  print_P(stream, typeTextCss);
  stream.write(charQuote);
  stream.write(charGreater);
  stream.write(charLF);
}

void EthWebServer::htmlPageStyleStart() {
  _htmlPageStyleStart(*_client);
}

static void _htmlPageStyleEnd(Stream& stream) {
  _htmlTagEnd(stream, tagStyle, true, true);
}

void EthWebServer::htmlPageStyleEnd() {
  _htmlPageStyleEnd(*_client);
}

static void _htmlPageStyle(Stream& stream, const char* style, bool file, bool progmem) {
  if (file) {
    stream.print(F("<link rel=\"stylesheet\" href=\""));
    if (progmem)
      print_P(stream, style);
    else
      stream.print(style);
    stream.print(F("\">\n"));
  } else {
    _htmlPageStyleStart(stream);
    if (progmem)
      print_P(stream, style);
    else
      stream.print(style);
    stream.write(charLF);
    _htmlPageStyleEnd(stream);
  }
}

void EthWebServer::htmlPageStyle(const char* style, bool file) {
  _htmlPageStyle(*_client, style, file, false);
}

void EthWebServer::htmlPageStyle_P(PGM_P style, bool file) {
  _htmlPageStyle(*_client, style, file, true);
}

void EthWebServer::htmlPageStdStyle() {
  _htmlPageStyle(*_client, pathStdStyle, true, true);
}

static void _htmlPageScriptStart(Stream& stream) {
  stream.write(charLess);
  print_P(stream, tagScript);
  stream.write(charSpace);
  print_P(stream, attrType);
  print_P(stream, typeTextJavascript);
  stream.write(charQuote);
  stream.write(charGreater);
  stream.write(charLF);
}

void EthWebServer::htmlPageScriptStart() {
  _htmlPageScriptStart(*_client);
}

static void _htmlPageScriptEnd(Stream& stream) {
  _htmlTagEnd(stream, tagScript, true, true);
}

void EthWebServer::htmlPageScriptEnd() {
  _htmlPageScriptEnd(*_client);
}

static void _htmlPageScript(Stream& stream, const char* script, bool file, bool progmem) {
  if (file) {
    stream.write(charLess);
    print_P(stream, tagScript);
    stream.write(charSpace);
    print_P(stream, attrType);
    print_P(stream, typeTextJavascript);
    stream.write(charQuote);
    stream.write(charSpace);
    print_P(stream, attrSrc);
    if (progmem)
      print_P(stream, script);
    else
      stream.print(script);
    stream.write(charQuote);
    stream.write(charGreater);
  } else {
    _htmlPageScriptStart(stream);
    if (progmem)
      print_P(stream, script);
    else
      stream.print(script);
    stream.write(charLF);
  }
  _htmlPageScriptEnd(stream);
}

void EthWebServer::htmlPageScript(const char* script, bool file) {
  _htmlPageScript(*_client, script, file, false);
}

void EthWebServer::htmlPageScript_P(PGM_P script, bool file) {
  _htmlPageScript(*_client, script, file, true);
}

void EthWebServer::htmlPageStdScript() {
  _htmlPageScript(*_client, pathStdScript, true, true);
}

static void _htmlPageBody(Stream& stream, const char* attrs, bool progmem) {
  _htmlTagEnd(stream, tagHead, true, true);
  _htmlTagStart(stream, tagBody, attrs, true, progmem);
}

void EthWebServer::htmlPageBody(const char* attrs) {
  _htmlPageBody(*_client, attrs, false);
}

void EthWebServer::htmlPageBody_P(PGM_P attrs) {
  _htmlPageBody(*_client, attrs, true);
}

void EthWebServer::htmlPageEnd() {
/*
  _client->print(F("</body>\n\
</html>"));
*/
  htmlTagEnd_P(tagBody, true);
  htmlTagEnd_P(tagHtml);
}

static void _escapeQuote(Stream& stream, const char* str, bool progmem) {
  char c;

  do {
    if (progmem)
      c = pgm_read_byte(str++);
    else
      c = *str++;
    if (c) {
      if (c == charQuote)
        print_P(stream, strCharQuote);
      else
        stream.print(c);
    }
  } while (c);
}

void EthWebServer::escapeQuote(const char* str) {
  _escapeQuote(*_client, str, false);
}

void EthWebServer::escapeQuote_P(PGM_P str) {
  _escapeQuote(*_client, str, true);
}

static void _htmlTag(Stream& stream, const char* type, const char* attrs, const char* content, bool newline, bool progmem) {
  if (content) {
/*
    print_P(stream, strTagOpen);
    if (progmem)
      print_P(stream, type);
    else
      stream.print(type);
    print_P(stream, strTagClose);
*/
    _htmlTagStart(stream, type, attrs, false, progmem);
    if (progmem)
      print_P(stream, content);
    else
      stream.print(content);
/*
    print_P(stream, strTagSlashOpen);
    if (progmem)
      print_P(stream, type);
    else
      stream.print(type);
    print_P(stream, strTagClose);
*/
    _htmlTagEnd(stream, type, false, progmem);
  } else {
    stream.write(charLess);
    if (progmem)
      print_P(stream, type);
    else
      stream.print(type);
    if (attrs) {
      stream.write(charSpace);
      if (progmem)
        print_P(stream, attrs);
      else
        stream.print(attrs);
    }
    stream.write(charSlash);
    stream.write(charGreater);
  }
  if (newline)
    stream.write(charLF);
}

void EthWebServer::htmlTag(const char* type, const char* attrs, const char* content, bool newline) {
  _htmlTag(*_client, type, attrs, content, newline, false);
}

void EthWebServer::htmlTag_P(PGM_P type, PGM_P attrs, PGM_P content, bool newline) {
  _htmlTag(*_client, type, attrs, content, newline, true);
}

static void _htmlTagInput(Stream& stream, const char* type, const char* name, const char* value, const char* attrs, bool newline, bool progmem) {
/*
  stream.print(F("<input type=\""));
*/
  stream.write(charLess);
  print_P(stream, tagInput);
  stream.write(charSpace);
  print_P(stream, attrType);
  if (progmem)
    print_P(stream, type);
  else
    stream.print(type);
  stream.write(charQuote);
  if (name) {
/*
    stream.print(F(" name=\""));
*/
    stream.write(charSpace);
    print_P(stream, attrName);
    if (progmem)
      print_P(stream, name);
    else
      stream.print(name);
    stream.write(charQuote);
  }
  if (value) {
/*
    stream.print(F(" value=\""));
*/
    stream.write(charSpace);
    print_P(stream, attrValue);
//    stream.print(value);
    _escapeQuote(stream, value, progmem);
    stream.write(charQuote);
  }
  if (attrs) {
    stream.write(charSpace);
    if (progmem)
      print_P(stream, attrs);
    else
      stream.print(attrs);
  }
/*
  print_P(stream, strTagSlashClose);
*/
  stream.write(charSlash);
  stream.write(charGreater);
  if (newline)
    stream.write(charLF);
}

void EthWebServer::htmlTagInput(const char* type, const char* name, const char* value, const char* attrs, bool newline) {
  _htmlTagInput(*_client, type, name, value, attrs, newline, false);
}

void EthWebServer::htmlTagInput_P(PGM_P type, PGM_P name, PGM_P value, PGM_P attrs, bool newline) {
  _htmlTagInput(*_client, type, name, value, attrs, newline, true);
}
