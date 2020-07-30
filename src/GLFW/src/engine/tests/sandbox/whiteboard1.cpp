//
// Created by vladl on 12/07/2020.
//

#include <iostream>
#include <obj/util/data/Map.h>
 #include <obj/util/shader/Shader.h>

using namespace engine;

int main() {
//    HashMap<String, String> tokens;
//
//    tokens.put(String("a"), String("bbb"));
//    tokens.put(String("b"), String("dddd"));
//    tokens.put(String("xyz"), String("eefef"));
//
//    Array<String*> keys = tokens.getKeys();
//    Array<String*> values = tokens.getValues();
//
//    for(std::size_t i = 0; i < keys.getLength(); i++) {
//        std::cout << (*keys[i]) << ' ';
//    }
//    std::cout << '\n';
//
//    for(std::size_t i = 0; i < values.getLength(); i++) {
//        std::cout << (*values[i]) << ' ';
//    }
//    std::cout << '\n';
//
//    std::cout << tokens << '\n';


    Shader::Header::Struct structTest("StructTest");
    structTest.addVariable("var123", Shader::Header::DataType::UINT16);
    structTest.addVariable("var231", Shader::Header::DataType::SINT8);
    structTest.addVariable("var", Shader::Header::DataType::SAMPLER_2D);
    structTest.addVariable("var3415", Shader::Header::DataType::MAT_4);

    structTest.addStructVariable("Light", "v123");
    structTest.addArrayStructVariable("Light", "v3242", 105);
    structTest.addArrayStructVariable("Dark", "skkr", 13244);
    structTest.addArrayStructVariable("Dark123", "skkr4", 13242);

    structTest.addArrayVariableFloat("var2312", 10);

//    std::cout << structTest.toString() << '\n';

    Shader::Header headerTest("headerGeneratAcum");

    headerTest.addStruct(structTest);

    auto pairs = headerTest.getDefinedStructures().getEntries();

    headerTest.addVariable(engine::String("var1"), structTest, engine::Shader::Header::DataTypeModifier::UNIFORM);
    headerTest.addVariable(engine::String("var2"), engine::Shader::Header::DataType::MAT_3);
    headerTest.addVariableMat3(engine::String("var4"));
    headerTest.addVariableSampler2D(engine::String("var3"));

    headerTest.addVariableVec4("test123", engine::Shader::Header::DataTypeModifier::INPUT);

    headerTest.addArrayVariableUInt64("etse", 1023, engine::Shader::Header::DataTypeModifier::OUTPUT );

    headerTest.generate();
}