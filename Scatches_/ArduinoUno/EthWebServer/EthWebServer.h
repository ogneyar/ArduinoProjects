#ifndef __ETHWEBSERVER_H
#define __ETHWEBSERVER_H

#include <avr/pgmspace.h>
#include <Stream.h>
#include <Ethernet.h>

//#define NDEBUG
//#define LIGHT

const char charNull = '\0';
const char charTab = '\t';
const char charLF = '\n';
const char charCR = '\r';
const char charSpace = ' ';
const char charQuestion = '?';
const char charPlus = '+';
const char charMinus = '-';
const char charPercent = '%';
const char charEqual = '=';
const char charLess = '<';
const char charGreater = '>';
const char charAmpersand = '&';
const char charColon = ':';
const char charSemicolon = ';';
const char charComma = ',';
const char charDot = '.';
const char charQuote = '"';
const char charApostrophe = '\'';
const char charSlash = '/';
const char charBackslash = '\\';

const char strEmpty[] PROGMEM = "";
const char strSlash[] PROGMEM = "/";

const char strCharSpace[] PROGMEM = "&nbsp;";
const char strCharQuote[] PROGMEM = "&quot;";

const char typeTextPlain[] PROGMEM = "text/plain";
const char typeTextHtml[] PROGMEM = "text/html";
const char typeTextJson[] PROGMEM = "text/json";
const char typeTextCss[] PROGMEM = "text/css";
const char typeTextJavascript[] PROGMEM = "text/javascript";
const char typeApplicationJavascript[] PROGMEM = "application/javascript";

const char tagHtml[] PROGMEM = "html";
const char tagHead[] PROGMEM = "head";
const char tagTitle[] PROGMEM = "title";
const char tagBody[] PROGMEM = "body";
const char tagStyle[] PROGMEM = "style";
const char tagScript[] PROGMEM = "script";
const char tagForm[] PROGMEM = "form";
const char tagBR[] PROGMEM = "br";
const char tagP[] PROGMEM = "p";
const char tagH1[] PROGMEM = "h1";
const char tagH2[] PROGMEM = "h2";
const char tagH3[] PROGMEM = "h3";
const char tagLabel[] PROGMEM = "label";
const char tagInput[] PROGMEM = "input";
const char tagSpan[] PROGMEM = "span";
const char tagTable[] PROGMEM = "table";
const char tagCaption[] PROGMEM = "caption";
const char tagTR[] PROGMEM = "tr";
const char tagTH[] PROGMEM = "th";
const char tagTD[] PROGMEM = "td";

const char attrType[] PROGMEM = "type=\"";
const char attrName[] PROGMEM = "name=\"";
const char attrValue[] PROGMEM = "value=\"";
const char attrSrc[] PROGMEM = "src=\"";
const char attrHref[] PROGMEM = "href=\"";

const char inputTypeText[] PROGMEM = "text";
const char inputTypePassword[] PROGMEM = "password";
const char inputTypeButton[] PROGMEM = "button";
const char inputTypeRadio[] PROGMEM = "radio";
const char inputTypeCheckbox[] PROGMEM = "checkbox";
const char inputTypeSubmit[] PROGMEM = "submit";
const char inputTypeReset[] PROGMEM = "reset";
const char inputTypeHidden[] PROGMEM = "hidden";

const char pathRoot[] PROGMEM = "/index.html";
const char pathStdStyle[] PROGMEM = "/std.css";
const char pathStdScript[] PROGMEM = "/std.js";

#ifndef NDEBUG
const char strNotEnoughMemory[] PROGMEM = "Not enough memory!";
const char strClientNotConnected[] PROGMEM = "Client not connected!";
const char strBadRequest[] PROGMEM = "Only HTTP 1.1 GET requests supported!";
#endif

struct pair_t {
  char* name;
  char* value;
};

class EthWebServer {
public:
  EthWebServer(uint16_t port = 80);
  ~EthWebServer();

  void begin();
  void handleClient();
  const char* uri() const {
    return _uri;
  }
  EthernetClient* client() {
    return _client;
  }
  uint8_t args() const {
    return _argCount;
  }
  const char* arg(const char* name);
  const char* arg_P(PGM_P name);
  const char* arg(uint8_t ind);
  const char* argName(uint8_t ind);
  bool hasArg(const char* name);
  bool hasArg_P(PGM_P name);
  uint8_t headers() const {
    return _headerCount;
  }
  const char* header(const char* name);
  const char* header_P(PGM_P name);
  const char* header(uint8_t ind);
  const char* headerName(uint8_t ind);
  bool hasHeader(const char* name);
  bool hasHeader_P(PGM_P name);
  bool send(int16_t code, const char* contentType, const char* content);
  bool send_P(int16_t code, PGM_P contentType, PGM_P content);
  bool sendHeader(const char* name, const char* value);
  bool sendHeader_P(PGM_P name, PGM_P value);
  bool sendContent(Stream& stream);
  bool sendContent(const char* content);
  bool sendContent_P(PGM_P content);

  void htmlPageStart(const char* title);
  void htmlPageStart_P(PGM_P title);
  void htmlPageStyleStart();
  void htmlPageStyleEnd();
  void htmlPageStyle(const char* style, bool file = false);
  void htmlPageStyle_P(PGM_P style, bool file = false);
  void htmlPageStdStyle();
  void htmlPageScriptStart();
  void htmlPageScriptEnd();
  void htmlPageScript(const char* script, bool file = false);
  void htmlPageScript_P(PGM_P script, bool file = false);
  void htmlPageStdScript();
  void htmlPageBody(const char* attrs = NULL);
  void htmlPageBody_P(PGM_P attrs = NULL);
  void htmlPageEnd();
  void htmlTagStart(const char* type, const char* attrs = NULL, bool newline = false);
  void htmlTagStart_P(PGM_P type, PGM_P attrs = NULL, bool newline = false);
  void htmlTagEnd(const char* type, bool newline = false);
  void htmlTagEnd_P(PGM_P type, bool newline = false);
  void htmlTag(const char* type, const char* attrs = NULL, const char* content = NULL, bool newline = false);
  void htmlTag_P(PGM_P type, PGM_P attrs = NULL, PGM_P content = NULL, bool newline = false);
  void htmlTagBR(bool newline = false) {
    htmlTag_P(tagBR, NULL, NULL, newline);
  }
  void htmlTagInput(const char* type, const char* name, const char* value, const char* attrs = NULL, bool newline = false);
  void htmlTagInput_P(PGM_P type, PGM_P name, PGM_P value, PGM_P attrs = NULL, bool newline = false);

  void escapeQuote(const char* str);
  void escapeQuote_P(PGM_P str);

  static PGM_P responseCodeToString(int16_t code);
  static char* urlDecode(char* decoded, const char* url);

protected:
  bool checkClient();
  bool startResponse(int16_t code, const char* contentType, int16_t contentLength = -1);
  bool startResponse_P(int16_t code, PGM_P contentType, int16_t contentLength = -1);
  bool endResponse();
  virtual void handleRequest(const char* uri);
  virtual void handleRootPage(const char* uri) = 0;
  virtual void handleNotFound(const char* uri);
  virtual void handleStdStyle(const char* uri);
  virtual void handleStdScript(const char* uri);
  bool parseRequest();
  bool parseArguments(const char* argList);
  bool parseHeaders(const char* headerList);

  static const uint16_t BUFFER_SIZE = 512;

  EthernetServer* _server;
  EthernetClient* _client;
  uint8_t _buffer[BUFFER_SIZE];
  uint16_t _bufferLength;
  char* _uri;
  uint8_t _argCount;
  pair_t* _args;
  uint8_t _headerCount;
  pair_t* _headers;

private:
  void clearArgs();
  void clearHeaders();
};

#endif
