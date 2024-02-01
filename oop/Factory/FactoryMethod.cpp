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
	virtual std::unique_ptr < Notification > create(std::string address) = 0;
};

class EmailCreator : public NotificationFactory {
public:
	std::unique_ptr < Notification > create(std::string address) override {
		return std::make_unique < EmailNotification >(address);
	}
};
class SMSCreator : public NotificationFactory {
public:
	std::unique_ptr < Notification > create(std::string address) override {
		return std::make_unique < SMSNotification >(address);
	}
};
class PushCreator : public NotificationFactory {
public:
	std::unique_ptr < Notification > create(std::string address) override {
		return std::make_unique < PushNotification >(address);
	}
};

class SPAM_System {
public:
	SPAM_System(std::unique_ptr < NotificationFactory > ptr) {
		factory = std::move(ptr);
	}
	void send_spam(std::string user, std::string message) {
		std::unique_ptr < Notification > new_notification = factory->create( user );
		new_notification->setMessage(message);
		new_notification->send();
	}
	void changeFactory( std::unique_ptr < NotificationFactory > ptr ) {
		factory = std::move(ptr);
	}
private:
	std::unique_ptr < NotificationFactory > factory;
};

int main() {
	SPAM_System spammer( std::make_unique < EmailCreator > () );

	spammer.send_spam( "IvanIvanovich@pochta.ru", "Subscribe to vgzowski on github" );

	spammer.send_spam( "IvanovIvan228@pochta.ru", "Subscribe to vgzowski on github" );

	spammer.changeFactory( std::make_unique < PushCreator > () );

	spammer.send_spam( "IvanIvanovich phone", "Subscribe to vgzowski on github" );

	spammer.send_spam( "IvanIvanovich smart watch", "Subscribe to vgzowski on github" );

	spammer.changeFactory( std::make_unique < SMSCreator > () );

	spammer.send_spam( "+1-23-34-5678-9-10", "Subscribe to vgzowski on github" );

	spammer.changeFactory( std::make_unique < PushCreator > () );

	spammer.send_spam( "IvanIvanovich TV", "Subscribe to vgzowski on github" );

	spammer.changeFactory( std::make_unique < EmailCreator > () );

	spammer.send_spam( "IvanIvanovichFakeEmail@pochta.ru", "Subscribe to vgzowski on github" );

	spammer.changeFactory( std::make_unique < SMSCreator > () );

	spammer.send_spam( "+12-34-567-89", "Subscribe to vgzowski on github" );
}
