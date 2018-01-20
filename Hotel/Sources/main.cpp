#include "../Headers/Hotel.h"

int main(int argc, char* argv[]) {
	Hotel* h = new Hotel(4);
	cout << *h << endl;
	h->feed_all();
	h->rest_all();
	h->train_all();
	h->feed_animal("Giraffe");

	h->add_animal("", "15/12/2017 - 08/01/2018", 15, 108); // X  . . . name is not valid
	h->add_animal("Dog", "15/12/2017 - 08/01/2018", 15, 108, 3, false, false); // ✔ . . .
	h->add_animal("Cat", "21/12/2017 - 27/01/2018", 14, 112, 5, false, false); // ✔ . . .
	h->add_animal("Lion", "27/12/2017 - 05/01/2018", 5, 112, 5, false, true); // X  . . . room occupied
	h->add_animal("Tiger", "08/01/2018 - 05/01/2018", 9, 123, 4, false, true); // ✔ . . .
	h->add_animal("Snake", "21/01/2018 - 26/01/2018", 1, 136, 4, false, true); // ✔ . . .
	h->add_animal("Cat", "14/01/2018 - 05/04/2018", 9, 137, 4, true, true); // X  . . . has the same animal
	h->add_animal("Aslan", "08/04/2018 - 05/08/2018", 11, 141, 5, false, false); // X  . . . capacity reached

	cout << endl << *h << endl;

	string s = "Tiger";
	h->remove_animal(s); // ✔ . . .
	s = "Zebra";
	h->remove_animal(s); // X  . . . hotel does not have such an animal
	h->register_food("Pineapple", "Cat Lion Tiger"); // ✔ . . . food will be registered
	h->register_food("Pineapple", "Tiger Elephant"); // ✔ . . . food will be updated
	h->register_food("Lemon", "Cat Lion"); // ✔ . . . food will be registered
	h->register_food("Ginger", "Cat Snake"); // ✔ . . . food will be registered
	h->add_animal("Elephant", "08/04/2018 - 05/08/2018", 20, 1441, 5, false, false);
	h->register_food("Strawberry", "Lion Tiger"); // ✔ . . . food will be registered
	h->register_food("Strawberry", "Giraffe Elephant"); // ✔ . . . food will be registered
	cout << endl << *h << endl;

	cout << "Hotel contains animal Tiger: " << h->contains_animal("Tiger") << endl;
	cout << "Hotel contains animal Cat: " << h->contains_animal("Cat") << endl;
	cout << "Animal count: " << h->animal_count() << endl;
	cout << "Hotel empty: " << h->is_empty() << endl;
	cout << "h[0]: " << (*h)[0] << endl;
	cout << "h[1]: " << h->operator[](1) << endl;
	cout << "h[2]: " << h->operator[](2) << endl;
	cout << "h[3]: " << h->operator[](3) << endl;
	Hotel h2(*h);
	h2 = *h;
	h->operator-=(4);
	h->operator-=(1);
	h->operator-=(2);
	cout << endl << *h << endl;

	cout << "\n\t\t*********H2********" << endl;
	h2--;
	--h2;
	cout << h2 << endl;
	h2.add_animal("Giraffe", "15/02/2018 - 26/05/2021", 6, 504);

	h2.print_animal_memory_addresses(); // 17368
	h2.print_food_memory_addresses(); // 400, 640

	cout << "Hotel has food pineapple? " << h2.contains_food("Pineapple") << endl;
	cout << "Hotel has food peach? " << h2.contains_food("Peach") << endl;

	h->feed_all();
	h2.feed_animal("Dog");
	h2.feed_animal("Cat");

	h->train_all();
	h2.train_all();
	h->rest_all();
	h2.rest_all();

	h2.modify("Dog", 12);
	h2.modify("Dog", true, true);
	h2.modify("ABC", 123);
	h2.modify("ABC", true, true);

	int a = -5;
	h2.transfer_animal("Dog", a);
	h2.transfer_animal("Dog", 504);
	h2.transfer_animal("ABC", 1700);
	h2.transfer_animal("ABC", 504);
	h2.transfer_animal("", 504);

	cout << "\n\t\t*********DISPLAY INFO*************" << endl;
	h2.display_info("Dog");
	h2.display_info("");

	h2.add_animal("Animal", "15/02/2018 - 26/05/2021", 6, 6007, 0, false, false);
	h2.register_food("ASD", "Animal");
	cout << h2 << endl;
	for (int i = 0; i < 6; ++i) {
		h2.train_all();
	}
	cout << h2 << endl;

	delete h;

	cout << *h << endl;

	system("pause");

	return 0;
}
