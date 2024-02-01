#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

void send_email(std::string email, std::string mes) {
	std::cout << "Sending email [" << mes << "] to email " << email << std::endl;	
}
void send_push(std::string device, std::string mes) {
	std::cout << "Sending push [" << mes << "] to device " << device << std::endl;
}
void send_sms(std::string number, std::string mes) {
	std::cout << "Sending sms [" << mes << "] to number " << number << std::endl;
}

class Notification {
public:
	std::string message;
	std::string source;
	void setMessage(std::string new_message) {
		message = new_message;
	}
	void setSource(std::string new_source) {
		source = new_source;
	}

	virtual void send() = 0;
};

class EmailNotification : public Notification {
public:
	EmailNotification(std::string email) {
		setSource(email);
	}
	void send() override {
		send_email( source, message );
	}
};
class SMSNotification : public Notification {
public:
	SMSNotification(std::string number) {
		setSource(number);
	}
	void send() override {
		send_sms( source, message );
	}
};
class PushNotification : public Notification {
public:
	PushNotification(std::string device) {
		setSource(device);
	}
	void send() override {
		send_push( source, message );
	}
};

class NotificationFactory {
public:
	std::unique_ptr < Notification > create(std::string type, std::string address) {
		if (type == "email") return std::make_unique< EmailNotification >(address);
		else if (type == "sms") return std::make_unique< SMSNotification >(address);
		else if (type == "push") return std::make_unique< PushNotification >(address);
		else throw std::runtime_error("Incorrect notification type");
	}
};

class SPAM_System {
public:
	SPAM_System(NotificationFactory _factory) : factory(factory) {}
	void send_spam(std::string type, std::string user, std::string message) {
		std::unique_ptr < Notification > new_notification = factory.create( type, user );
		new_notification->setMessage(message);
		new_notification->send();
	}
private:
	NotificationFactory factory;
};

int main() {
}
