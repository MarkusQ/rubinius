#include <stdio.h>
#include <string.h>

#include "ruby.h"
#include "rubyspec.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_RB_CALL_SUPER
static VALUE class_spec_call_super_method(VALUE self) {
  return rb_call_super(0, 0);
}

static VALUE class_spec_define_call_super_method(VALUE self, VALUE obj, VALUE str_name) {
  rb_define_method(obj, RSTRING_PTR(str_name), class_spec_call_super_method, 0);
  return Qnil;
}
#endif

#ifdef HAVE_RB_CLASS2NAME
static VALUE class_spec_rbclass2name(VALUE self, VALUE klass) {
  return rb_str_new2( rb_class2name(klass) );
}
#endif

#ifdef HAVE_RB_CLASS_INHERITED
static VALUE class_spec_rb_class_inherited(VALUE self, VALUE super, VALUE klass) {
  if(super == Qfalse) {
    return rb_class_inherited((VALUE)(0), klass);
  } else {
    return rb_class_inherited(super, klass);
  }
}
#endif

#ifdef HAVE_RB_CLASS_NEW
static VALUE class_spec_rb_class_new(VALUE self, VALUE super) {
  return rb_class_new(super);
}
#endif

#ifdef HAVE_RB_CLASS_NEW_INSTANCE
static VALUE class_spec_rb_class_new_instance(VALUE self,
                                      VALUE nargs, VALUE args,
                                      VALUE klass) {
  int c_nargs = FIX2INT(nargs);
  VALUE c_args[c_nargs];
  int i;

  for (i = 0; i < c_nargs; i++)
    c_args[i] = rb_ary_entry(args, i);

  return rb_class_new_instance(c_nargs, c_args, klass);
}

#endif

#ifdef HAVE_RB_CVAR_DEFINED
static VALUE class_spec_cvar_defined(VALUE self, VALUE klass, VALUE id) {
  ID as_id = rb_intern(StringValuePtr(id));
  return rb_cvar_defined(klass, as_id);
}
#endif

#ifdef HAVE_RB_CVAR_GET
static VALUE class_spec_cvar_get(VALUE self, VALUE klass, VALUE name) {
	return rb_cvar_get(klass, rb_intern(StringValuePtr(name)));
}
#endif

#ifdef HAVE_RB_CVAR_SET
static VALUE class_spec_cvar_set(VALUE self, VALUE klass, VALUE name, VALUE val) {
	rb_cvar_set(klass, rb_intern(StringValuePtr(name)), val, 0);

  return Qnil;
}
#endif

#ifdef HAVE_RB_CV_GET
static VALUE class_spec_cv_get(VALUE self, VALUE klass, VALUE name) {
	return rb_cv_get(klass, StringValuePtr(name));
}
#endif

#ifdef HAVE_RB_CV_SET
static VALUE class_spec_cv_set(VALUE self, VALUE klass, VALUE name, VALUE val) {
	rb_cv_set(klass, StringValuePtr(name), val);

  return Qnil;
}
#endif

#ifdef HAVE_RB_DEFINE_ATTR
VALUE class_spec_define_attr(VALUE self, VALUE klass, VALUE sym, VALUE read, VALUE write) {
  int int_read, int_write;
  int_read = read == Qtrue ? 1 : 0;
  int_write = write == Qtrue ? 1 : 0;
  rb_define_attr(klass, rb_id2name(SYM2ID(sym)), int_read, int_write);
  return Qnil;
}
#endif

#ifdef HAVE_RB_DEFINE_CLASS_VARIABLE
static VALUE class_spec_define_class_variable(VALUE self, VALUE klass, VALUE name, VALUE val) {
  rb_define_class_variable(klass, StringValuePtr(name), val);
  return Qnil;
}
#endif

#ifdef HAVE_RB_INCLUDE_MODULE
static VALUE class_spec_include_module(VALUE self, VALUE klass, VALUE module) {
  rb_include_module(klass, module);
  return klass;
}
#endif

void Init_class_spec() {
  VALUE cls;
  cls = rb_define_class("CApiClassSpecs", rb_cObject);

#ifdef HAVE_RB_CALL_SUPER
  rb_define_method(cls, "define_call_super_method", class_spec_define_call_super_method, 2);
#endif

#ifdef HAVE_RB_CLASS2NAME
  rb_define_method(cls, "rb_class2name", class_spec_rbclass2name, 1);
#endif

#ifdef HAVE_RB_CLASS_INHERITED
  rb_define_method(cls, "rb_class_inherited", class_spec_rb_class_inherited, 2);
#endif

#ifdef HAVE_RB_CLASS_NEW
  rb_define_method(cls, "rb_class_new", class_spec_rb_class_new, 1);
#endif

#ifdef HAVE_RB_CLASS_NEW_INSTANCE
  rb_define_method(cls, "rb_class_new_instance", class_spec_rb_class_new_instance, 3);
#endif

#ifdef HAVE_RB_CVAR_DEFINED
  rb_define_method(cls, "rb_cvar_defined", class_spec_cvar_defined, 2);
#endif

#ifdef HAVE_RB_CVAR_GET
  rb_define_method(cls, "rb_cvar_get", class_spec_cvar_get, 2);
#endif

#ifdef HAVE_RB_CVAR_SET
  rb_define_method(cls, "rb_cvar_set", class_spec_cvar_set, 3);
#endif

#ifdef HAVE_RB_CV_GET
  rb_define_method(cls, "rb_cv_get", class_spec_cv_get, 2);
#endif

#ifdef HAVE_RB_CV_SET
  rb_define_method(cls, "rb_cv_set", class_spec_cv_set, 3);
#endif

#ifdef HAVE_RB_DEFINE_ATTR
  rb_define_method(cls, "rb_define_attr", class_spec_define_attr, 4);
#endif

#ifdef HAVE_RB_DEFINE_CLASS_VARIABLE
  rb_define_method(cls, "rb_define_class_variable", class_spec_define_class_variable, 3);
#endif

#ifdef HAVE_RB_INCLUDE_MODULE
  rb_define_method(cls, "rb_include_module", class_spec_include_module, 2);
#endif
}

#ifdef __cplusplus
}
#endif
