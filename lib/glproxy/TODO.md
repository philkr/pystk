* Implement function hook
The glad_set_post_callback's should also contains 
the return value
```
// this symbol only exists if generated with the c-debug generator
#define GLAD_DEBUG
typedef void (* GLADcallback)(const char *name, void *funcptr, int len_args, ...);

/*
 * Sets a callback which will be called before every function call
 * to a function loaded by glad.
 *
 */
GLAPI void glad_set_pre_callback(GLADcallback cb);

/*
 * Sets a callback which will be called after every function call
 * to a function loaded by glad.
 *
 */
GLAPI void glad_set_post_callback(GLADcallback cb);
```

* Add OSX support

* Add RPI support

* Add tizen support

* Add WinPhone support

* Document, Enable faster feature test, but can not using variable, using 
```
glproxy_has_gl_extension_by_enum
```
for 
```
    if(GL_EXT_framebuffer_multisample) { 
        /* GL_EXT_framebuffer_multisample is supported */ 
    }

    if(GL_VERSION_3_0) {
        /* We support at least OpenGL version 3 */
    }
```

* Implement glproxy_has_gl_extension directly with the OpenGL funciton, now using
  enum
