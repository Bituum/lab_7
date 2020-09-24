#include <iostream>
#include <fstream>
#include <string>
#include "all_of_classes.hpp"

int main() {
    std::ifstream myfile;
    myfile.open("file.txt");
    Article *article = TXTArcticleBuilder(myfile).build();
    auto builder = XMLArticleBuilder();
    builder.setHeader(article->getHeader());
    builder.setAuthor(article->getAuthor());
    builder.setContent(article->getContent());
    auto xml = builder.build();
    std::ofstream myfile2;
    myfile2.open("article.xml");
    myfile2 << *xml;
    myfile.close();
    myfile2.close();
return 0;
}
