#include "all_of_classes.hpp"
#include <functional>
#include <ostream>
#include <string>



Article::Article(std::string &header, std::string &content, std::string &author, int hash)
    : header(header), content(content), author(author), hash(hash) {}


const std::string& Article::getAuthor() const
{
    return author;
}

const std::string& Article::getContent() const
{
    return content;
}

const std::string& Article::getHeader() const
{
    return header;
}

int Article::getHash() const
{
    return hash;
}

std::ostream &operator<<(std::ostream &os, const Article &article)
{
    article.print(os);
    return os;
}

void TXTArcticle::print(std::ostream &os) const
{
    os << this->getHeader() << "\n" << this->getAuthor() << 
    "\n" << this->getContent() << "\n" << this->getHash() << "\n";
}

void XMLArticle::print(std::ostream &os) const
{
    os << "<article>" << "\t\n<header>" << this->getHeader() << "</header>\n"
    << "\t<author>" << this->getAuthor() << "</author> \n"
    << "\t<content>" << this->getContent() << "</content>" << "\n"
    << "\t<hash>" << this->getHash() << "</hash>\n"
    << "</article>";
}

int ArticleBuilder::hash()
{
    std::hash<std::string> hashh;
    return hashh(this->content);
}

TXTArcticleBuilder::TXTArcticleBuilder(std::istream& is) : ArticleBuilder(), in(is) {}


Article* TXTArcticleBuilder::build()
{
    std::string author;
    std::string header;
    int hash;
    std::getline(in, author);
    std::getline(in, header);
    
    this->content = "";
    while(in)
    {
        char cr;
        in.read(&cr, 1);
        this->content.push_back(cr);
    }
    if(this->content.back() == '\n')
    {
        this->content.pop_back();
    }
    hash = this->hash();

    TXTArcticle* article = new TXTArcticle(header, content, author, hash);
    
    return article;
}

Article* XMLArticleBuilder::build()
{
    int hash = this->hash();
    return new XMLArticle(header, content, author, hash);
}
