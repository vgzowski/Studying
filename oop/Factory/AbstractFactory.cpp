#include <iostream>
#include <string>
#include <memory>

class Table {
public:
	virtual void PlaceObj(std::string obj) = 0;
};
class Chair {
public:
	virtual void Sit() = 0;
};

class CasualTable : public Table {
public:
	void PlaceObj(std::string obj) override {
		std::cout << "Now " << obj << " is placed on a table" << std::endl;
	}
};
class VictorianTable : public Table {
public:
	void PlaceObj(std::string obj) override {
		std::cout << "You want to place " << obj << " on such an old authentic table?" << std::endl;
	}
};

class CasualChair : public Chair {
public:
	void Sit() override {
		std::cout << "You sat down" << std::endl;
	}
};
class VictorianChair : public Chair {
public:
	void Sit() override {
		std::cout << "You can't sit down on this masterpiece" << std::endl;
	}
};

class Factory {
public:
	virtual std::unique_ptr <Chair> createChair() = 0;
	virtual std::unique_ptr <Table> createTable() = 0;
};

class CasualFactory : public Factory {
public:
	std::unique_ptr <Chair> createChair() override {
		return std::make_unique< CasualChair >();
	}
	std::unique_ptr <Table> createTable() override {
		return std::make_unique< CasualTable >();
	}
};
class VictorianFactory : public Factory {
public:
	std::unique_ptr <Chair> createChair() override {
		return std::make_unique< VictorianChair >();
	}
	std::unique_ptr <Table> createTable() override {
		return std::make_unique< VictorianTable >();
	}
};

class HouseDecorator {
public:
	HouseDecorator( std::unique_ptr <Factory> ptr ) {
		factory = std::move(ptr);
	}
	void decorate() {
		std::unique_ptr <Chair> chair = factory->createChair();
		std::unique_ptr <Table> table = factory->createTable();
		chair->Sit();
		table->PlaceObj("Vase");
	}
	void changeFactory( std::unique_ptr <Factory> ptr ) {
		factory = std::move(ptr);
	}
private:
	std::unique_ptr <Factory> factory;
};

int main() {
	HouseDecorator hs( std::make_unique < CasualFactory > () );
	hs.decorate();
	hs.decorate();
	hs.changeFactory( std::make_unique < VictorianFactory> () );
	hs.decorate();
	hs.changeFactory( std::make_unique < VictorianFactory> () );
	hs.decorate();
	hs.changeFactory( std::make_unique < CasualFactory> () );
	hs.decorate();
}
