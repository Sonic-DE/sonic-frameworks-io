# Sonic Frameworks IO Release Notes

Sonic Frameworks IO is the file access layer behind SonicDE, letting apps open, copy and browse files locally and over the network.

## 6.31.0 (2026-10-20)

- Behind the scenes: version number updated for this release.

## 6.30.0 (2026-09-12)

- Behind the scenes: version number updated for this release.

## 6.29.0.1 (2026-08-20)

- Behind the scenes: removed leftover code that caused build warnings.

## 6.29.0 (2026-08-07)

- Behind the scenes: cleaned up the way background file workers shut down, fixing a build problem.

## 6.28.0 (2026-07-03)

- Behind the scenes: better support for code editors and restored the project's code formatting rules.

## 6.27.0 (2026-06-11)

No SonicDE-specific changes in this release; it brings the package up to date with upstream.

## 6.26.0 (2026-05-01)

- Behind the scenes: stricter code quality checks, better support for code editors, tidier code with fewer build warnings, and the help page viewer no longer relies on an outdated function.

## 6.24.0 (2026-03-04)

- Launching apps, opening folders in the file manager and handling file places now use one streamlined path built for SonicDE's X11 desktop, with unused Wayland-only code removed.
