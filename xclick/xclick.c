#include <stdio.h>
#include <string.h>
#include <ruby.h>
#include <X11/Xlib.h>

VALUE XClick = Qnil;
void Init_xclick();
VALUE method_click(VALUE);
void click_d(Display*, int);

void Init_xclick() {
  XClick = rb_define_module("XClick");
  rb_define_singleton_method(XClick, "click", method_click, 0);
}

VALUE method_click(VALUE self) {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Could not open display.\n");
    return Qfalse;
  }
  click_d(display, Button1);
  XCloseDisplay(display);
  return Qtrue;
}

void click_d(Display *display, int button) {
  XEvent event;
  memset(&event, 0, sizeof(event));
  event.xbutton.button = button;
  event.xbutton.same_screen = True;
  event.xbutton.subwindow = DefaultRootWindow(display);
 
  while (event.xbutton.subwindow) {
    event.xbutton.window = event.xbutton.subwindow;
    XQueryPointer(display, event.xbutton.window, &event.xbutton.root,
                  &event.xbutton.subwindow, &event.xbutton.x_root,
                  &event.xbutton.y_root, &event.xbutton.x, 
                  &event.xbutton.y, &event.xbutton.state);
  }
 
  event.type = ButtonPress;
  if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0)
    fprintf(stderr, "Error -- could not sent event.\n");
  XFlush(display);
  usleep(1);
  
  event.type = ButtonRelease;
  if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0)
    fprintf(stderr, "Error -- could not sent event.\n");
  XFlush(display);
  usleep(1);
}
