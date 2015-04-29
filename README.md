# sound-to-dmx
Avr-based line level audio to dmx interface.

Controller that takes in 4 balances audio signals and converts them to dmx signals for driving a dmx dimmer and to three separate signals suitable for triggering optocouplers. The setup for which this controller was built consists of 24 light bulbs to be controlled with 3 dmx channels and 3 singular light bulbs that do not warrant separate dmx channels but a simply dimmed with triac sitting on the other side of an array of optocouplers.
