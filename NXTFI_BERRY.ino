
#include <WiFi.h>
#include <WebServer.h>
#include "FS.h"
#include "SPIFFS.h"
#include <berry.h>
//#include <be_repl.h>
#include <be_vm.h>

//berry only is 340651 freeram

#include <Ticker.h>

WebServer server(80);
Ticker tick;
const char* ssid = "MikroTik0";
const char* password = "";


extern "C" {
  void be_load_baselib(bvm *vm);
}

void handleTest(){
  
}

void memory_check() {
  Serial.printf_P(PSTR("Mem Free: %d\n"), free);
  Serial.printf_P(PSTR("Free Heap: %d\n"), ESP.getFreeHeap());
#ifdef ESP8266
  Serial.printf_P(PSTR("Fragmentation: %d\n"), ESP.getHeapFragmentation());
  Serial.printf_P(PSTR("Max Free Heap: %d\n"), ESP.getMaxFreeBlockSize());
#endif
}


/* portable readline function package */
/*
static const char* get_line(const char *prompt)
{
  static char buffer[1000];
  fputs(prompt, stdout);
  fflush(stdout);

  //  if (be_readstring(buffer, sizeof(buffer))) {
  //    buffer[strlen(buffer) - 1] = '\0';
  //    return buffer;
  //  }
  while (1) {
    if (Serial.available()) {
      String cmd = Serial.readStringUntil('\n');
      strcpy(buffer, cmd.c_str());
      return buffer;
    }
  }
  return NULL;
}
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  SPIFFS.begin();
  server.on("/test",handleTest);
  server.begin();
  
  Serial.printf("PULLUP: %d", PULLUP);
  Serial.printf("PULLDOWN: %d", PULLDOWN);
  Serial.println("starting vm");
  tick.attach(10, memory_check);
  bvm *vm = be_vm_new();
  be_dostring(vm, "print(\"this is the repl\")");

  /* // repl has memory leak
    char cmd[] = "print(\"Hello world!\")";
    be_pushstring(vm, cmd);
    int res = be_repl(vm, &get_line);
    if (res == -BE_MALLOC_FAIL) {
      be_writestring("error: memory allocation failed.\n");
    }
  */
  be_vm_delete(vm);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buffer[1000];
  if (Serial.available()) {
    bvm *vm = be_vm_new();
    String cmd = Serial.readStringUntil('\n');
    strcpy(buffer, cmd.c_str());
    be_dostring(vm, buffer);
    be_vm_delete(vm);
  }
}
