#pragma once
#include "Wt/Dbo/Dbo.h"
#include "Wt/Dbo/backend/Postgres.h"
#include <iostream>

class Book;

class Publisher {
public:
    std::string name = "";
    Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;

    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
    }
};

class Stock;

class Book {
public:
    std::string title = "";
    Wt::Dbo::ptr<Publisher> publisher;
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;
    template <class Action>

    void persist(Action& a) {
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, publisher, "publisher");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToMany, "book");

    }
};

class Stock;

class Store {
public:
    std::string name = "";
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToMany, "store");
    }
};

class Sale;

class Stock {
public:
    int count = 0;
    Wt::Dbo::ptr<Book> book;
    Wt::Dbo::ptr<Store> store;
    Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;

    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::belongsTo(a, book, "book");
        Wt::Dbo::belongsTo(a, store, "store");
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
    }

};

class Sale {
public:
    float price = 0.0f;
    std::string date = "";
    Wt::Dbo::ptr<Stock> stock;
    int count = 0;

    template <class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, price, "price");
        Wt::Dbo::field(a, date, "date_sale");
        Wt::Dbo::belongsTo(a, stock, "stock");
        Wt::Dbo::field(a, count, "count");
    }
};