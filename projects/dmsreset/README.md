# DMSReset 1.0 for MSP430

This is a Dead Mans Switch for annoying electronic equipment that just won't stay
alive (such as wireless routers that keep on crashing).

## The circuit

The circuit is simple. Create a voltage divider between the photoresistor and ground:

    VDD (+3.3V)                    GND
        |                   47K     |
        +----/\/\/----+----/\/\/----+
              ^^^     |
                  Sense Pin

Then, add the leds:

    Status Led                Alert Led
        |     ,,     470          |     ,,     470
        +----|>|----/\/\/----+    +----|>|----/\/\/----+
                             |                         |
                            GND                       GND

And finally the relay

     Relay Pin      Wall wart
        |     ____     | |
        +----|§  /|----+ |    You can power the MSP430 from here, by
             |§ | |      |    using a LM317 regulator to give you the
        +----|§___|----+ |    3.3V needed.
        |              | |
       GND          To device

## Compile options

 * `-DWITH_ACTIVE_LOW` -- if your device's status led goes dark on activity.
 * `-DWITH_ACTIVE_HIGH` -- if your device's status led flashes on activity. This is default
 * `-DTRIGGER_RESET=n` -- wait roughly n seconds before triggering a reset. Use with...
 * `-DTRIGGER_SLEEP=n` -- sleep roughly n seconds before turning the power back on.
