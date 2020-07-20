//
// Created by loghin on 7/15/20.
//


#include <obj/util/data/String.h>

#include <cstdio>

using namespace engine;

void basicTests () {
    std::cout << "////  BASIC TESTS \\\\\\\\\n\n\n";

    String a("abcdef");
    String b("abcdef", 4);
    String c(a);
    String d(b);

    String e;
    String f(4);

    std::cout << a << '\n';
    std::cout << b << '\n';
    std::cout << c << '\n';
    std::cout << d << '\n';
    std::cout << e << '\n';
    std::cout << f << '\n';

    std::cout << a.printInfo() << '\n';
    std::cout << b.printInfo() << '\n';
    std::cout << c.printInfo() << '\n';
    std::cout << d.printInfo() << '\n';
    std::cout << e.printInfo() << '\n';
    std::cout << f.printInfo() << '\n';

    std::string basicString = "xyzt";

    String g(basicString);
    String h(basicString, 3);

    std::cout << g << '\n';
    std::cout << h << '\n';

    std::cout << g.printInfo() << '\n';
    std::cout << h.printInfo() << '\n';

    String i(a, 5);

    std::cout << i << '\n';
    std::cout << i.printInfo() << '\n';
}

void accessTests() {

    std::cout << "////  ACCESS TESTS \\\\\\\\\n\n\n";

    String sample("Ana are mere");

    std::cout << sample << '\n' << sample.printInfo() << '\n';

    for(std::size_t it = 0; it < sample.length(); it++) {
        std::cout << sample[it] << ' ';
    }

    std::cout << '\n';

    for(std::size_t it = 0; it < sample.length(); it++) {
        std::cout << sample.get(it) << ' ';
    }

    std::cout << '\n';

    for(std::size_t it = 0; it < sample.length(); it++) {
        std::cout << String::get(sample,it) << ' ';
    }

    std::cout << '\n';

    for(std::size_t it = 0, length = sample.length() ; it < length / 2; it++) {
        char aux = sample[length - it - 1];
        sample[length - it - 1] = sample[it];
        sample[it] = aux;
    }

    std::cout << sample.printInfo() << '\n';
}

void utilityTests() {

    std::cout << "////  UTILITY TESTS \\\\\\\\\n\n\n";

    String sample("Ana are mere");

    std::cout << sample.printInfo() << '\n';

    std::cout << sample.reverse().printInfo() << '\n';

    std::cout << sample.printInfo() << '\n';

    std::cout << sample.getReversed().printInfo() << '\n';

    std::cout << sample.printInfo() << '\n';

    sample.reverse();

    std::cout << sample.printInfo() << "\n\n";

    std::cout << sample.substring(2, 10).printInfo() << '\n';

    std::cout << String::substring(sample, 5, 6).printInfo() << '\n';

    std::cout << sample.substring(6, 3).printInfo() << '\n';

    try{
        std::cout << sample.substring(-2, 10).printInfo() << '\n';// will throw exception with index close to uint64 cap.
        // indexes are unsigned, by assigning -2 to uint64 value, it does neg overflow => UINT64_MAX - 2
    } catch (engine::StringAccessOutOfBounds& exception) {
        std::cout << "Access out of bounds : " << exception.what() << '\n';
    }

    try{
        std::cout << sample.substring(3, 100).printInfo() << '\n';// will throw exception
    } catch (engine::StringAccessOutOfBounds& exception) {
        std::cout << "Access out of bounds : " << exception.what() << '\n';
    }

    String text("dffabcdabcdacdadeabcaed");

    std::cout << text.contains("abc") << '\n';

    std::cout << sample.split(' ') << '\n';

    std::cout << "Length check : \n\n";

    String sampleWithSpaces("    Ana         are  mere        ");

    Array<String> bits = sampleWithSpaces.split(' ');

    for(std::size_t it = 0 ; it < bits.getLength(); it++)
        std::cout << "\"" << bits[it] << "\"\n";

    std::cout << "First occurrence position of \"abc\" : " << text.findFirst("abc") << '\n';

    std::cout << "All occurrences positions of \'d\' : " << text.findAll('d') << '\n';
    std::cout << "All occurrences positions of \"abc\" : " << text.findAll("abc") << '\n';

    std::cout << "Last occurrence of \'d\' : " << text.findLast('d') << '\n';
    std::cout << "Last occurrence of \"abc\" : " << text.findLast("abc") << '\n';
}

void utility2Tests() {

    std::cout << "////  UTILITY TESTS (cont.) \\\\\\\\\n\n\n";

    String sample("abcdeffedcba");

    std::cout << sample.replace('d', "XX").replace('b', "YYY").printInfo() << '\n';

    std::cout << sample.split(' ') << '\n';

    std::cout << sample.replace("ff", " panamea ").printInfo() << '\n';
    std::cout << sample.replace("a", "ZZ").printInfo() << '\n';
    std::cout << sample.replace("e", 'R').printInfo() << '\n';

    std::cout << ((((sample += " bcde ") += " psde ") += " aced ") += " afaegfaedfaefa ").printInfo() << '\n';

    std::cout << sample.replace(3, 5, 'h').printInfo() << '\n';

    std::cout << sample.replace(10, 22, " plm ").printInfo() << '\n';

    std::cout << sample.replaceFirst('Y', " pnm ").printInfo() << '\n';

    std::cout << sample.replaceFirst("X", 'a').printInfo() << '\n';

    std::cout << sample.replaceLast('e', "XYZ").printInfo() << '\n';

    std::cout << sample.replaceLast(' ', "space").printInfo() << '\n';

    std::cout << sample.replaceLast("aced", 'f').printInfo() << '\n';
}

void fileTests() {
    std::ifstream file;

    file.open("sampleFile.txt");

    String line;
    try {
        while (String::getline(file, line))
//            std::cout << line.printInfo();
            std::cout << line << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    std::cout << line << '\n';

//    std::cout << "\n\n" << (uint16)line[line.length() - 1] << '\n';

    file.close();

    file.open("sampleFile.txt");

    String word;

    String::get(file, word);

    std::cout << word << '\n';

    String::get(file, word);

    std::cout << word << '\n';

    String::get(file, word);

    std::cout << word << '\n';
    String::get(file, word);

    std::cout << word << '\n';
}

void utility3Tests(){
    String sample("               abcd     e          ");
    std::cout << sample.ltrim(" ac").printInfo() << '\n';
    std::cout << sample.rtrim(' ').printInfo() << '\n';
    std::cout << sample.rtrim(" e").printInfo() << '\n';

//    std::cout << sample.ltrim("bcd").printInfo() << '\n';
//    std::cout << sample.rtrim("bcd").printInfo() << '\n';
    std::cout << sample.trim("bcd").printInfo() << '\n';
}

void operatorTests() {
    String a("abd"), b("abd");

    std::cout << (a >= b) << '\n';

    String c("fff");

    std::cout << c + a + " xez " + b << '\n';

    std::cin >> b;

    std::cout << " haha " + b + " haha " << '\n';
}

int main(){ 
//    basicTests();
//    accessTests();
//    utilityTests();
//    utility2Tests();
//    fileTests();
//    utility3Tests();
    operatorTests();
}

