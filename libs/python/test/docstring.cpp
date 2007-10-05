// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/docstring_options.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/manage_new_object.hpp>
#include "test_class.hpp"

// Just use math.h here; trying to use std::pow() causes too much
// trouble for non-conforming compilers and libraries.
#include <math.h>

using namespace boost::python;

typedef test_class<> X;

X* create(int x)
{
    return new X(x);
}

unsigned long fact(unsigned long n)
{
    return n <= 1 ? n : n * fact(n - 1);
}

BOOST_PYTHON_MODULE(docstring_ext)
{
    scope().attr("__doc__") =
        "A simple test module for documentation strings\n"
        "Exercised by docstring.py"
        ;

    class_<X>("X",
              "A simple class wrapper around a C++ int\n"
              "includes some error-checking"

              , init<int>(
                  "this is the __init__ function\n"
                  "its documentation has two lines."
                )

        )
        .def("value", &X::value,
             "gets the value of the object")
        .def( "value", &X::value,
            "also gets the value of the object")
        ;

    def("create", create, return_value_policy<manage_new_object>(),
        "creates a new X object");

    def("fact", fact, "compute the factorial");

    {
      docstring_options doc_options;
      doc_options.disable_user_defined();
      def("fact_usr_off_1", fact, "usr off 1");
      doc_options.enable_user_defined();
      def("fact_usr_on_1", fact, "usr on 1");
      doc_options.disable_user_defined();
      def("fact_usr_off_2", fact, "usr off 2");
    }
    def("fact_usr_on_2", fact, "usr on 2");

    {
      docstring_options doc_options(true, false);
      def("fact_sig_off_1", fact, "sig off 1");
      doc_options.enable_signatures();
      def("fact_sig_on_1", fact, "sig on 1");
      doc_options.disable_signatures();
      def("fact_sig_off_2", fact, "sig off 2");
    }
    def("fact_sig_on_2", fact, "sig on 2");

    {
      docstring_options doc_options(false);
      def("fact_usr_off_sig_off_1", fact, "usr off sig off 1");
      {
        docstring_options nested_doc_options;
        def("fact_usr_on_sig_on_1", fact, "usr on sig on 1");
        nested_doc_options.disable_all();
        nested_doc_options.enable_user_defined();
        def("fact_usr_on_sig_off_1", fact, "usr on sig off 1");
        nested_doc_options.enable_all();
        def("fact_usr_on_sig_on_2", fact, "usr on sig on 2");
      }
      def("fact_usr_off_sig_off_2", fact, "usr off sig off 2");
    }
}

#include "module_tail.cpp"
