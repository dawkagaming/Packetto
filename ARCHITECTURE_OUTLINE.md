# Project outline

## Receiving data

I had an idea to format data from every source into text APRS, like on APRS-IS and then push it to an asynchronous queue (GLib provides one), then to be picked by parser and processed into internal data used then by the programs.
