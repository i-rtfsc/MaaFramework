#include "quickjs.h"
#include <iostream>
#include <string>

int main()
{
    auto runtime = JS_NewRuntime();
    auto context = JS_NewContext(runtime);
    std::string code = "'Hello world!'";
    auto value = JS_Eval(context, code.c_str(), code.size(), "a.js", 0);
    if (JS_VALUE_GET_TAG(value) == JS_TAG_STRING) {
        std::cout << JS_ToCString(context, value) << std::endl;
    }
    JS_FreeContext(context);
    JS_FreeRuntime(runtime);
}
