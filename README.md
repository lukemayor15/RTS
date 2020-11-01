# RTS

Developed with Unreal Engine 4.25.1

This project is currently in development and there are some know issues.
1. The current method of checking if a building can be placed uses on overlap begin and end. therefore, if the mouse moves to quickly the on-collision overlap begin/end is not trigger.
2. The AI Navigation for the units is untuned, therefore they do get caught on buildings and edges
3.When the AI units move, they currently required to reach the exact position to stop, this is going to be change to within a range.
