//  Wayland from Scratch
//  Copyright (C) 2024 Ezekiel Holliday
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "license.h"

//
// This function dertermines the name of the Unix Domain
// port to use when attempting to connecting to the Wayland
// compositer.
//
// If there is an errror, the returned structurture will be empty.
//
[[nodiscard]] static struct sockaddr_un getDisplayName() {
  struct sockaddr_un name = {.sun_family = AF_UNIX};
  char *dest = &name.sun_path[0];
  const char *const end = dest + sizeof(name.sun_path) - 1;

  const char *wayland_display = getenv("WAYLAND_DISPLAY");
  const char *display = "wayland-0";
  const char *xdg_runtime_dir = getenv("XDG_RUNTIME_DIR");

  if (wayland_display) {
    display = wayland_display;
  }
  assert(nullptr != display);

  if (nullptr == xdg_runtime_dir) {
    fprintf(stderr, "XDG_RUNTIME_DIR undefined");
    return (struct sockaddr_un){};
  }

  if (*xdg_runtime_dir == '\0' || *display == '\0') {
    fprintf(stderr, "XDG_RUNTIME_DIR or WAYLAND_DISPLAY defined as a zero"
                    " length string\n");
    return (struct sockaddr_un){};
  }

  while ('\0' != *xdg_runtime_dir && dest != end) {
    *dest++ = *xdg_runtime_dir++;
  };

  if (*xdg_runtime_dir != '\0') {
    fprintf(stderr, "XDG_RUNTIME_DIR too long");
    return (struct sockaddr_un){};
  }

  if (*dest != '/' && dest != end) {
    *dest++ = '/';
  }

  while ('\0' != *display && dest != end) {
    *dest++ = *display++;
  };

  if (*display != '\0') {
    fprintf(stderr, "display too long");
    return (struct sockaddr_un){};
  }

  return name;
};

int main(int argn, char *argv[]) {

  // TODO: FIX the arguements
  if (argn > 1) {
    if (0 == strcmp("--L", argv[1])) {
      printf("%s\n", license);
    }
    return 0;
  }

  printf("%s\n", license_banner);

  struct sockaddr_un name = getDisplayName();
  printf("%s\n", name.sun_path);
}
