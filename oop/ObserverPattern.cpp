#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void getNotified(std::string r) = 0;
	virtual void react() = 0;
};
class IPublisher {
public:
	virtual ~IPublisher() {}

	virtual void Notify() = 0;
	virtual void AddObserver(IObserver*) = 0;
	virtual void DelObserver(IObserver*) = 0;
protected:
	std::list <IObserver*> obs;
};

class Newspaper : public IPublisher {
public:
	void change_news(std::string str) {
		latest_news = str;
		Notify();
	}
	void AddObserver(IObserver* nw) override {
		obs.push_back(nw);
	}
	void DelObserver(IObserver* nw) override {
		auto it = std::find(obs.begin(), obs.end(), nw);
		obs.erase(it);
	}
private:
	std::string latest_news = "";
	void Notify() override {
		auto it = obs.begin();
		while (it != obs.end()) {
			(*it)->getNotified(latest_news);
			++it;
		}
	}
};

class PersonA : public IObserver {
public:
	void getNotified(std::string r) override {
		std::cout << "I don't care that the news are [" << r << "]" << std::endl;
		reaction = r + ", but I don't care";
	}
	void react() override {
		std::cout << "My honest reaction: " << reaction << std::endl;
	}
	~PersonA() {}
private:
	std::string reaction = "";
};
class PersonB : public IObserver {
public:
	void getNotified(std::string r) override {
		std::cout << "I care that the news are [" << r << "]" << std::endl;
		reaction = r.size() + 0.5;
	}
	void react() override {
		std::cout << "I am " << reaction << "percent angry" << std::endl;
	}
	~PersonB() {}
private:
	double reaction = 0;
};

int main() {
	PersonA a1, a2, a3;
	PersonB b1, b2;

	Newspaper times, tg_bot;
	times.AddObserver(&a1);
	times.AddObserver(&a3);
	times.AddObserver(&b1);
	times.AddObserver(&b2);

	tg_bot.AddObserver(&a2);
	tg_bot.AddObserver(&a3);
	tg_bot.AddObserver(&b2);

	std::vector <IObserver*> ptr = {&a1, &a2, &a3, &b1, &b2};

	for (const auto &x : ptr) {
		x->react();
	}

	times.change_news("Dollar is now 1.2 PLN");
	tg_bot.change_news("Hee-Hoo");

	for (const auto &x : ptr) {
		x->react();
	}

	times.DelObserver(&b1);
	times.DelObserver(&a3);

	times.change_news("Dollar is now 228 PLN");
	tg_bot.change_news("Hee-Hoo i am a dancing guy");

	for (const auto &x : ptr) {
		x->react();
	}
}
