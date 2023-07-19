#include "CPP_ORM2.h"

class Book;
class Publisher;
class Book;
class Stock;
class Sale;
class Store;

void findStore(Wt::Dbo::Session& session, std::string namePublisher) {
	Wt::Dbo::ptr<Publisher> findPublisher = session.find<Publisher>().where("name = ?").bind(namePublisher);
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books = session.find<Book>().where("publisher_id = ?").bind(findPublisher);
	std::vector<Wt::Dbo::collection<Wt::Dbo::ptr<Stock>>> stocks;
	for (const auto& id : books) {
		stocks.push_back(session.find<Stock>().where("book_id = ?").bind(id.id()));
	}
	std::vector<Wt::Dbo::collection<Wt::Dbo::ptr<Store>>> shops;
	for (const auto& col : stocks) {
		for (const auto& id : col) {
			shops.push_back(session.find<Store>().where("id = ?").bind(id->store));
		}
	}
	std::cout << "Shops with books of " << namePublisher << ": \n";
	std::set<std::string> names;
	for (const auto& col : shops) {
		for (const auto& id : col) {
			names.insert(id->name);
		}
	}
	for (const auto& name : names) {
		std::cout << name << std::endl;
	}
}

int main() {
	try {
		std::string connectionString =
			"host=localhost "
			" port=5432"
			" dbname=newDB"
			" user=postgres"
			" password=1990";
		auto postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);
		Wt::Dbo::Session session;
		session.setConnection(std::move(postgres));
		session.mapClass<Book>("book");
		session.mapClass<Publisher>("publisher");
		session.mapClass<Store>("store");
		session.mapClass<Stock>("stock");
		session.mapClass<Sale>("sale");
		session.createTables();

		Wt::Dbo::Transaction transaction{ session };

		std::unique_ptr<Publisher> Drofa{new Publisher()};
		Drofa->name = "Drofa";
		Wt::Dbo::ptr<Publisher> Drofa_ptr = session.add(std::move(Drofa));

		std::unique_ptr<Publisher> Binom{new Publisher()};
		Binom->name = "Binom";
		Wt::Dbo::ptr<Publisher> Binom_ptr = session.add(std::move(Binom));

		std::unique_ptr<Publisher> Fenix{new Publisher()};
		Fenix->name = "Fenix";
		Wt::Dbo::ptr<Publisher> Fenix_ptr = session.add(std::move(Fenix));


		std::unique_ptr <Book> Idiot{new Book()};
		Idiot->title = "Idiot";
		Idiot->publisher = Drofa_ptr;
		Wt::Dbo::ptr<Book> idiot_ptr = session.add(std::move(Idiot));


		std::unique_ptr <Book> Idiot2{new Book()};
		Idiot2->title = "Idiot";
		Idiot2->publisher = Binom_ptr;
		Wt::Dbo::ptr<Book> Idiot2_ptr = session.add(std::move(Idiot2));


		std::unique_ptr <Book> Idiot3{new Book()};
		Idiot3->title = "Idiot";
		Idiot3->publisher = Fenix_ptr;
		Wt::Dbo::ptr<Book> Idiot3_ptr = session.add(std::move(Idiot3));


		std::unique_ptr <Book> HarryPotter{new Book()};
		HarryPotter->title = "Harry Potter";
		HarryPotter->publisher = Drofa_ptr;
		Wt::Dbo::ptr<Book> HarryPotter_ptr = session.add(std::move(HarryPotter));


		std::unique_ptr <Book> HarryPotter2{new Book()};
		HarryPotter2->title = "Harry Potter";
		HarryPotter2->publisher = Binom_ptr;
		Wt::Dbo::ptr<Book> HarryPotter2_ptr = session.add(std::move(HarryPotter2));


		std::unique_ptr <Book> HarryPotter3{new Book()};
		HarryPotter3->title = "Harry Potter";
		HarryPotter3->publisher = Fenix_ptr;
		Wt::Dbo::ptr<Book> HarryPotter3_ptr = session.add(std::move(HarryPotter3));


		std::unique_ptr<Store> DomKnigi{new Store()};
		DomKnigi->name = "DomKnigi";
		Wt::Dbo::ptr<Store> DomKnigi_ptr = session.add(std::move(DomKnigi));
		std::unique_ptr<Store> Bukvoed{new Store()};
		Bukvoed->name = "Bukvoed";
		Wt::Dbo::ptr<Store> Bukvoed_ptr = session.add(std::move(Bukvoed));
		std::unique_ptr<Store> Piter{new Store()};
		Piter->name = "Piter";
		Wt::Dbo::ptr<Store> Piter_ptr = session.add(std::move(Piter));



		std::unique_ptr<Stock> stockPiter{new Stock()};
		stockPiter->book = idiot_ptr;
		stockPiter->store = DomKnigi_ptr;
		stockPiter->count = 100;
		Wt::Dbo::ptr<Stock> stockPiter_ptr = session.add(std::move(stockPiter));

		std::unique_ptr<Stock> stockPiter2{new Stock()};
		stockPiter2->book = HarryPotter_ptr;
		stockPiter2->store = Bukvoed_ptr;
		stockPiter2->count = 150;
		Wt::Dbo::ptr<Stock> stockPiter2_ptr = session.add(std::move(stockPiter2));

		std::unique_ptr<Stock> stockPiter3{new Stock()};
		stockPiter3->book = HarryPotter_ptr;
		stockPiter3->store = Piter_ptr;
		stockPiter3->count = 160;
		Wt::Dbo::ptr<Stock> stockPiter3_ptr = session.add(std::move(stockPiter3));

		std::unique_ptr<Stock> stockPiter4{new Stock()};
		stockPiter4->book = HarryPotter_ptr;
		stockPiter4->store = Piter_ptr;
		stockPiter4->count = 100;
		Wt::Dbo::ptr<Stock> stockPiter4_ptr = session.add(std::move(stockPiter4));

		std::unique_ptr<Sale> sale_1{new Sale()};
		sale_1->price = 100;
		sale_1->date = "2020-07-20";
		sale_1->stock = stockPiter_ptr;
		sale_1->count = 20;

		session.add(std::move(sale_1));
		std::unique_ptr<Sale> sale_2{new Sale()};
		sale_2->price = 50;
		sale_2->date = "2020-07-20";
		sale_2->stock = stockPiter2_ptr;
		sale_2->count = 10;

		session.add(std::move(sale_2));
		std::unique_ptr<Sale> sale_3{new Sale()};
		sale_3->price = 80;
		sale_3->date = "2020-07-20";
		sale_3->stock = stockPiter3_ptr;
		sale_3->count = 30;

		session.add(std::move(sale_3));
		std::unique_ptr<Sale> sale_4{new Sale()};
		sale_4->price = 111;
		sale_4->date = "2020-07-20";
		sale_4->stock = stockPiter4_ptr;
		sale_4->count = 40;
		session.add(std::move(sale_4));

		std::string namePublisher = "";
		std::cout << "Input name of publisher: ";
		std::cin >> namePublisher;
		findStore(session, namePublisher);
		transaction.commit();
	}
	catch (const Wt::Dbo::Exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}

