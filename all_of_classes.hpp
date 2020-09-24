#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

class Article
{
    private:
        int hash;
        std::string author;
        std::string header;
        std::string content;
    protected:
        Article(std::string &header, std::string &content, std::string &author, int hash);
        virtual void print(std::ostream &os) const = 0;

    public:
        virtual ~Article(){};

        friend std::ostream &operator<<(std::ostream &os, const Article &article);

        const std::string &getAuthor() const;
        const std::string &getHeader() const;
        const std::string &getContent() const;
        int getHash() const;
};


class TXTArcticle : public Article
{
    protected:

        void print(std::ostream &os) const override;

    public:
        virtual ~TXTArcticle() = default;
        TXTArcticle(std::string &header, std::string &content, std::string &author, int hash)
            : Article(header, content, author, hash) {}
};

class XMLArticle : public Article
{
    protected:
        
        void print(std::ostream &os) const override;

    public:
        virtual ~XMLArticle() = default;
        XMLArticle(std::string &header, std::string &content, std::string &author, int hash)
            : Article(header, content, author, hash) {}
};

class ArticleBuilder
{
    public:
        std::string content;
        int hash();
        ArticleBuilder() = default;
        virtual Article* build() = 0;
        virtual ~ArticleBuilder() = default;
        
};


class TXTArcticleBuilder : public ArticleBuilder
{
    private:
        std::istream &in;
    public:
        TXTArcticleBuilder(std::istream &is);
        ~TXTArcticleBuilder() = default;
        virtual Article* build() override;
};


class XMLArticleBuilder : public ArticleBuilder
{
    private:

        std::string header;
        std::string author;

    public:
        XMLArticleBuilder() = default;
        ~XMLArticleBuilder() = default;
        
        const std::string& getHeader() const 
        {
            return header;
        }

        void setHeader(const std::string &header)
        {
            XMLArticleBuilder::header = header;      
        }

        
        const std::string& getContent() const 
        {
            return content;
        }

        void setContent(const std::string &content)
        {
            XMLArticleBuilder::content = content;      
        }

        
        const std::string& getAuthor() const 
        {
            return author;
        }

        void setAuthor(const std::string &author)
        {
            XMLArticleBuilder::author = author;      
        }

        Article* build() override;
};

