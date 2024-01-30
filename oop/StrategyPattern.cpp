#include <iostream>
#include <vector>

class FlyBehaiviour {
public:
	virtual void Fly() = 0;
	virtual ~FlyBehaiviour() {}
};
class CanFly : public FlyBehaiviour {
public:
	void Fly() override {
		std::cout << "I am flying" << std::endl;
	}
	~CanFly() {}
};
class CanNotFly : public FlyBehaiviour {
public:
	void Fly() override {
		std::cout << "I am NOT flying" << std::endl;
	}
	~CanNotFly() {}
};

class IsBillionaire {
public:
	virtual void spend1mil() = 0;
	virtual ~IsBillionaire() {}
};
class TopG : public IsBillionaire {
public:
	void spend1mil() override {
		std::cout << "Just spent 1 mil on a watch" << std::endl;
	}
	~TopG() {}
};
class Brokie : public IsBillionaire {
public:
	void spend1mil() override {
		std::cout << "Can't afford lunch" << std::endl;
	}
	~Brokie() {}
};

class Duck {
public:
	void Swim() { std::cout << "I am swimming" << std::endl; }
	void Exist() { std::cout << "I am existing" << std::endl; }

	FlyBehaiviour* canFly = nullptr;
	void Fly() { canFly->Fly(); }
	void changeFly(FlyBehaiviour* nw) {
		if (canFly != nullptr) delete canFly;
		canFly = nw;
	}

	IsBillionaire* bil = nullptr;
	void Spend() { bil->spend1mil(); }
	void changestatus(IsBillionaire* nw) {
		if (bil) delete bil;
		bil = nw;
	}

	virtual void print() {
		std::cout << "I am just a duck" << std::endl;
	}
};

class RubberDuck : public Duck {
public:
	RubberDuck() {
		changeFly( new CanNotFly() );
		changestatus( new TopG() );
	}

	void print() override {
		std::cout << "I am a rubber duck" << std::endl;
	}
};
class BelDuck : public Duck {
public:
	BelDuck() {
		changeFly( new CanFly() );
		changestatus( new Brokie() );
	}

	void print() override {
		std::cout << "I am a bel duck" << std::endl;
	}
};
class TopGDuck : public Duck {
public:
	TopGDuck() {
		changeFly( new CanFly() );
		changestatus( new TopG() );
	}

	void print() override {
		std::cout << "I am a Top G" << std::endl;
	}
};

int main() {
	RubberDuck rub;
	BelDuck bl;
	TopGDuck pankin;

	std::cout << "RubberDuck:" << std::endl;
	rub.Swim();
	rub.Exist();
	rub.Fly();
	rub.Spend();

	std::cout << std::endl;

	std::cout << "BelDuck:" << std::endl;
	bl.Swim();
	bl.Exist();
	bl.Fly();
	bl.Spend();

	std::cout << "Changed" << std::endl;

	bl.changeFly(new CanNotFly());
	bl.Swim();
	bl.Exist();
	bl.Fly();
	bl.Spend();

	std::cout << std::endl;

	std::cout << "Top G duck:" << std::endl;
	pankin.Swim();
	pankin.Exist();
	pankin.Fly();
	pankin.Spend();

	std::cout << std::endl;

	std::vector <Duck*> pointers{ &rub, &bl, &pankin, new Duck(), &bl };
	for (const auto &x : pointers) {
		x->print();
	}
}
