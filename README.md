# Packetto

Packetto aims to be a simple and easy to use APRS graphical client, written using C++ and LibAdwaita.

## Building

On Debian:

```bash
sudo apt -U install build-essential cmake pkgconf gettext \
    libgtk-4-dev libadwaita-1-dev libshumate-dev
```

To generathe the C++ bindings you need [peel-gen](https://gitlab.gnome.org/bugaevc/peel), which is not yet available in the archive, but can be downloaded from CI/CD artifacts here: <https://salsa.debian.org/gnome-team/extras/peel>

Then you can build the project using `cmake . && cmake --build .`

## Contributing

You are very encouraged to add PRs!

Here is the simple outline what has been added/completed and what hasn't been.

Ideas about the architecture are of course welcome!

Take a look at [ARCHITECTURE_OUTLINE.md](ARCHITECTURE_OUTLINE.md)

**GUI**
- [ ] Main window
- [ ] Preferences window
- [x] About window
- [ ] Vector maps support

**Networking**
- [ ] KISS over Serial
- [ ] KISS over TCP
- [ ] AGWPE
- [ ] APRS-IS

**Misc**
- [ ] INI Parser (for usage with settings)

**Art**
- [ ] Application logo
- [ ] UI icons
- [ ] APRS icons
