#include <iostream>

#include <rttr/type.h>

#include "Scene/Component/Transform.hpp"
using namespace fly;

int main(int argc, char const *argv[])
{
    rttr::type t = rttr::type::get<Transform>();

    for (auto &prop : t.get_properties())
        std::cout << "name: " << prop.get_name();
    for (auto &meth : t.get_methods())
        std::cout << "name: " << meth.get_name();
    std::cout << "end " << std::endl;
    auto pos = t.get_by_name("position");

    Transform obj;

    rttr::property prop = rttr::type::get(obj).get_property("position");
    prop.set_value(obj, Vector3f(1.f, 1.f, 1.f));
    auto vt = prop.get_type();
    for (auto &prop1 : vt.get_properties())
        std::cout << "name: " << prop1.get_name();
    for (auto &meth1 : vt.get_methods())
        std::cout << "name: " << meth1.get_name();
    std::cout << "end " << std::endl;
    // auto json_string = rttr::io::to_json(obj);  // serialize the circle to 'json_string'
}
