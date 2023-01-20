#include <Express.h>
using namespace EXPRESS_NAMESPACE;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

express app;

void setup() {
  Serial.begin(115200);
  while (!Serial && !Serial.available()) {}

  Ethernet.begin(mac);

  app.get("/", [](request &req, response &res) {
    res.send("Got a GET request");
  });

  app.post("/", [](request &req, response &res) {
    res.send("Got a POST request");
  });

  app.put("/user", [](request &req, response &res) {
    res.send("Got a PUT request at /user");
  });

  app.Delete("/user", [](request &req, response &res) {
    res.send("Got a DELETE request at /user");
  });

  app.listen(80, []() {
    Serial.print(F("Example app listening on port "));
    Serial.print(Ethernet.localIP());
    Serial.print(F(" "));
    Serial.println(app.port);
  });
}

void loop() {
  app.run();
}
