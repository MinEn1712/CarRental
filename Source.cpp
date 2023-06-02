#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>

using namespace std;
#define MaxID 50
#define MaxPass 50

struct Car //Used enter the information of the added car
{
	string Brand;
	string PlateNumber;
	string Color;
	long RentalFee = 0;
	string Status;
};
struct REGISTER //Make a new account
{
	string id;
	string pass;
};
struct LOGIN //Login to an existing account
{
	string UserID;
	string password;
};

void Add(Car& car) //Add car option
{
	//Clear screen
	system("cls");

	//Add car menu
	cout << endl;
	cout << "---------- ADD CAR ----------" << endl;
	cout << "Brand: "; cin >> car.Brand;
	cout << "Plate Number: "; cin >> car.PlateNumber;
	cout << "Color: "; cin >> car.Color;
	cout << "Price: "; cin >> car.RentalFee;
	cout << "-----------------------------" << endl;
	car.Status = "O"; //Rental status to Available
	cout << endl;

	cout << " *** Added successfully ***" << endl;
	cout << "View list to see all the cars!" << endl;
	cout << endl;

	//Declare and open Car List.txt
	ofstream Add_Car;
	Add_Car.open("Car List.txt", ios_base::app);

	//Add car's information to Car List.txt 
	Add_Car << car.PlateNumber << ' ';
	Add_Car << car.Brand << ' ';
	Add_Car << car.Color << ' ';
	Add_Car << car.RentalFee << ' ';
	Add_Car << car.Status << ' ';
	Add_Car << "_ " << endl; //Means no one has rented

	/*In Car List.txt the display will be: e.g.  123456KA KIA Red 30 O _*/

	//Close Car List.txt
	Add_Car.close();
}

void Delete(string plate) //Delete car option
{
	//Count if there is an existing plate number on the list
	int count = 0;

	//Buffer to store information temporarily
	string buffer;
	string plate_num;
	string copy;
	string brand;
	string color;
	string price;
	string status;
	string user;

	//Declare and open Car List.txt and Delete Car.txt file
	ifstream delete_car;
	ofstream after_list;
	delete_car.open("Car List.txt", ios_base::in);
	after_list.open("Delete Car.txt", ios_base::out);

	//Check each line in Car List.txt
	while (getline(delete_car, buffer)) //Put information of a line in to variable buffer
	{
		//Copy buffer to iss (e.g. buffer = "123456KA KIA Red 30 O _")
		istringstream iss(buffer);

		//Assign the plate number in iss to plate_num (e.g. iss = "123456KA KIA Red 30 O _" so plate_num = "123456KA")
		getline(iss, plate_num, ' ');

		//Check if plate_num is the same as the input
		if (plate_num != plate)
		{
			//Write the whole buffer to Delete Car.txt
			after_list << buffer << endl;
		}
		else
		{
			//count if there is a plate number on the list
			count++;
			//Assign each info of the car to variables brand, color, price and status

			getline(iss, brand, ' '); //iss = "KIA Red 30 O _" --> brand = "KIA"
			getline(iss, color, ' '); //iss = "Red 30 O _" --> color = "Red"
			getline(iss, price, ' '); //iss = "30 O _" --> price = "30"
			getline(iss, status, ' '); //iss = "O _" --> status = "O"
			getline(iss, user, ' '); //iss = "_" --> user = "_"

			//Check if the status if available
			if (status == "O")
				continue;
			else
			{
				cout << endl;
				cout << "Can't delete! This car is currently rented." << endl;
				after_list << buffer << endl;
			}
		}
	}

	cout << endl;
	//if count < 1 than the car is not on the list
	if (count < 1) cout << "This plate number is not on the list!" << endl;

	//Close Car List.txt and Delete Car.txt
	delete_car.close();
	after_list.close();

	/*Copy the whole thing from Delete Car.txt to Car List.txt*/
	//Declare and open Car List.txt and Delete Car.txt file 
	ifstream delete_list;
	ofstream new_list;
	delete_list.open("Delete Car.txt", ios_base::in);
	new_list.open("Car List.txt", ios_base::out);

	/*Copy*/
	while (getline(delete_list, copy))
	{
		new_list << copy << endl;
	}

	//Close Car List.txt and Delete Car.txt file
	delete_list.close();
	new_list.close();

	cout << "View car list to see updates!" << endl;
	cout << endl;
}

void Rental(string plate, string user_id, int days) //Rent car option
{
	//Count if there is an existing plate number on the list
	int count = 0;
	//Choice if you sure you want to rent
	int choice;

	//Buffer to store information temporarily
	string buffer;
	string plate_num;
	string copy;
	string brand;
	string color;
	string price;
	string status;
	string user;

	//Declare and open Car List.txt and Rental.txt
	ifstream chosen_car;
	ofstream rental;
	chosen_car.open("Car List.txt", ios_base::in);
	rental.open("Rental.txt", ios_base::out);

	//Check each line in Car List.txt
	while (getline(chosen_car, buffer)) //Put information of a line in to variable buffer
	{
		//Copy buffer to iss (e.g. buffer = "123456KA KIA Red 30 O _")
		istringstream iss(buffer);

		//Assign the plate number in iss to plate_num (e.g. iss = "123456KA KIA Red 30 O _" so plate_num = "123456KA")
		getline(iss, plate_num, ' ');

		//Check if plate_num is the same as the input
		if (plate_num == plate)
		{
			//count if there is a plate number on the list
			count++;

			//Write plate_num to Rental.txt
			rental << plate_num << " ";

			getline(iss, brand, ' '); //iss = "KIA Red 30 O _" --> brand = "KIA"
			//Write brand to Rental.txt
			rental << brand << " ";

			getline(iss, color, ' '); //iss = "Red 30 O _" --> color = "Red"
			//Write color to Rental.txt
			rental << color << " ";

			getline(iss, price, ' '); //iss = "30 O _" --> price = "30"
			//Write price to Rental.txt
			rental << price << " ";

			getline(iss, status, ' '); //iss = "O _" --> status = "O"
			getline(iss, user, ' '); //iss = "_" --> user = "_"

			if (status == "X") //If the car is currently rented --> Not available
			{
				cout << endl;
				cout << "This car is not available." << endl;
				rental << status << " ";
				rental << user << endl;
			}
			else
			{
				//Check if the user really want to rent
				cout << endl;
				cout << "Are you sure you want to rent?" << endl;
				cout << "(Yes: 1, No: 0)" << endl;
				cout << "Choice: ";  cin >> choice;

				//Check choice
				if (choice == 1)
				{
					//Output the price
					cout << endl;
					stringstream num(price); //Turn the price from string to number
					int n; num >> n;
					cout << "Total price >> " << "$" << n * days << endl; //Calculate the price

					//Change rental status to rented and add user id
					status = "X";
					user = user_id;
					rental << status << ' ';
					rental << user << endl;
				}
				else if (choice == 0)
				{
					rental << status << ' ';
					rental << user << endl;
				}
				else
				{
					cout << "Invalid input! Please enter 1 or 0." << endl;
					rental << status << ' ';
					rental << user << endl;
				}
			}
		}
		else
		{
			rental << buffer << endl; //Write the not-chosen cars to Rental.txt
		}
	}

	cout << endl;

	//if count < 1 than the car is not on the list
	if (count < 1) cout << "This plate number is not on the list!" << endl;

	//Close Car List.txt and Rental.txt
	chosen_car.close();
	rental.close();

	/*Copy the whole thing from Rental.txt to Car List.txt*/
	//Declare and open Car List.txt and Rental.txt
	ifstream rent_list;
	ofstream new_list;
	rent_list.open("Rental.txt", ios_base::in);
	new_list.open("Car List.txt", ios_base::out);

	/*Copy*/
	while (getline(rent_list, copy))
	{
		new_list << copy << endl;
	}

	//Close Car List.txt and Rental.txt
	rent_list.close();
	new_list.close();

	cout << "View car list to see updates!" << endl;
	cout << endl;
}

void Return(string plate, string user_id) //Return car option
{
	//Count if there is an existing plate number on the list
	int count = 0;

	//Buffer to store information temporarily
	string buffer;
	string plate_num;
	string copy;
	string brand;
	string color;
	string price;
	string status;
	string user;

	//Declare and open Car List.txt and Return.txt
	ifstream chosen_car;
	ofstream return_car;
	chosen_car.open("Car List.txt", ios_base::in);
	return_car.open("Return.txt", ios_base::out);

	//Check each line in Car List.txt
	while (getline(chosen_car, buffer)) //Put information of a line in to variable buffer
	{
		//Copy buffer to iss (e.g. buffer = "123456KA KIA Red 30 X username123")
		istringstream iss(buffer);

		//Assign the plate number in iss to plate_num (e.g. iss = "123456KA KIA Red 30 X username123" so plate_num = "123456KA")
		getline(iss, plate_num, ' ');

		//Check if plate_num is the same as the input
		if (plate_num == plate)
		{
			//count if there is a plate number on the list
			count++;

			//Write plate_num to Return.txt
			return_car << plate_num << " ";

			getline(iss, brand, ' '); //iss = "KIA Red 30 X username123" --> brand = "KIA"
			//Write brand to Return.txt
			return_car << brand << " ";

			getline(iss, color, ' '); //iss = "Red 30 X username123" --> color = "Red"
			//Write color to Return.txt
			return_car << color << " ";

			getline(iss, price, ' '); //iss = "30 X username123" --> price = "30"
			//Write price to Return.txt
			return_car << price << " ";

			getline(iss, status, ' '); //iss = "X username123" --> status = "X"
			getline(iss, user, ' '); //iss = "username123" --> user = "username123"

			//Check status
			if (status == "X")
			{
				if (user_id == user)
				{
					status = "O"; //Return to available
					user = "_"; //Return rented by no one
					return_car << status << " ";
					return_car << user << endl;
				}
				else
				{
					cout << endl;
					cout << "This car is currently rented by another user!" << endl;
					return_car << status << " ";
					return_car << user << endl;
				}
			}
			else
			{
				cout << endl;
				cout << "Can't return! This car is currently available." << endl; //Can't return an available car
				return_car << status << " ";
				return_car << user << endl;
			}
		}
		else
		{
			return_car << buffer << endl; //Write the not-chosen cars to Return.txt
		}
	}

	cout << endl;
	//if count < 1 than the car is not on the list
	if (count < 1) cout << "This plate number is not on the list!" << endl;

	//Close Car List.txt and Return.txt
	chosen_car.close();
	return_car.close();

	/*Copy the whole thing from Return.txt to Car List.txt*/
	//Declare and open Car List.txt and Return.txt
	ifstream return_list;
	ofstream new_list;
	return_list.open("Return.txt", ios_base::in);
	new_list.open("Car List.txt", ios_base::out);

	/*Copy*/
	while (getline(return_list, copy))
	{
		new_list << copy << endl;
	}

	//Close Car List.txt and Return.txt
	return_list.close();
	new_list.close();

	cout << "View car list to see updates!" << endl;
	cout << endl;
}

void View(Car& car)
{
	//Clear screen
	system("cls");

	//Buffer to store information temporarily
	string brand;
	string plate;
	string color;
	string price;
	string status;
	string user;
	string buffer;

	//Output car list
	cout << endl;
	cout << "-------------------------------------------- CAR LIST --------------------------------------------" << endl;
	cout << "Plate Number         Brand          Color          Price          Status          Rented By" << endl;
	cout << "--------------------------------------------------------------------------------------------------" << endl;

	//Declare and open Car List.txt
	ifstream car_list;
	ofstream view_car;
	car_list.open("Car List.txt", ios_base::in);

	//Check each line in Car List.txt
	while (getline(car_list, buffer)) //Put information of a line in to variable buffer
	{
		//Copy buffer to iss (e.g. buffer = "123456KA KIA Red 30 O _")
		istringstream iss(buffer);

		//Assign the plate number in iss to plate_num (e.g. iss = "123456KA KIA Red 30 O _" so plate_num = "123456KA")
		getline(iss, plate, ' ');
		cout << plate;
		for (int i = 1; i < (10 + (12 - plate.length())); i++) //Add spaces to make the table neat 
			cout << " ";

		getline(iss, brand, ' '); //iss = "KIA Red 30 O _" --> brand = "KIA"
		cout << brand;
		for (int i = 0; i < (10 + (5 - brand.length())); i++) //Add spaces to make the table neat
			cout << " ";

		getline(iss, color, ' '); //iss = "Red 30 O _" --> color = "Red"
		cout << color;
		for (int i = 0; i < (10 + (5 - color.length())); i++) //Add spaces to make the table neat
			cout << " ";

		getline(iss, price, ' '); //iss = "30 O _" --> price = "30"
		cout << "$" << price;
		for (int i = 0; i < (10 + (5 - price.length()) + 1); i++) //Add spaces to make the table neat
			cout << " ";

		getline(iss, status, ' '); //iss = "O _" --> status = "O"
		cout << status << "             "; //Add spaces to make the table neat

		getline(iss, user, ' '); //iss = "_" --> user = "_"
		cout << user << endl;
	}

	//Close Car List.txt
	car_list.close();
	cout << "----------------------------------- O: Available; X: Rented ------------------------------------" << endl;
	cout << endl;
}

int Welcome(int& Option) //Option: login or register
{
	//Login menu
	cout << endl;
	cout << "     - WELCOME TO CAR RENTAL -" << endl;
	cout << endl;
	cout << "       ********************" << endl;
	cout << "       *   1. Login       *" << endl;
	cout << "       *   2. Register    *" << endl;
	cout << "       ********************" << endl;
	cout << endl;
	cout << "If you have an account, press 1 to login." << endl;
	cout << "If not, press 2 to register." << endl;
	cout << "Your option: "; cin >> Option;
	return Option;
}
int Menu(int& choice) //Service menu
{
	system("color 0F");
	cout << endl;
	cout << "           - MENU -           " << endl;
	cout << "   -------------------------" << endl;
	cout << "   |   1. Add Car          |" << endl;
	cout << "   |   2. View Car         |" << endl;
	cout << "   |   3. Delete Car       |" << endl;
	cout << "   |   4. Rent Car         |" << endl;
	cout << "   |   5. Return Car       |" << endl;
	cout << "   |   6. Exit             |" << endl;
	cout << "   -------------------------" << endl;
	cout << endl;
	cout << "Choose an option: "; cin >> choice;
	cout << endl;
	return choice;
}

int Login(LOGIN& user) //Login option chosen in Welcome()
{
	//ID and Password buffer
	char str[20];
	string buffer;
	string check;

	for (int i = 0; i < 3; i++)
	{
		cout << endl;
		fflush(stdin); //Delete cache

		//Enter ID and Password
		cout << "---------- LOGIN ----------" << endl;
		cout << "User ID: "; cin.ignore();  cin.getline(str, MaxID);
		user.UserID = str;
		_flushall();
		cout << "Password: "; cin.getline(str, MaxPass);
		user.password = str;
		cout << "---------------------------" << endl;
		cout << endl;

		//Open User.txt
		ifstream FileIn;
		FileIn.open("User.txt", ios_base::in);
		//Buffer used to check ID and Password
		while (getline(FileIn, buffer)) //Put information in a line to variable buffer
		{
			//Copy buffer to iss (e.g. buffer = "username password")
			istringstream iss(buffer);

			//Assign iss to check (e.g. iss = "username password" --> check = "username")
			getline(iss, check, ' ');

			//Check if the input user name is correct
			if (check == user.UserID)
			{
				getline(iss, check, ' '); //iss = "password" --> check == "password"

				//Check if the password is correct
				if (check == user.password)
				{
					cout << "Logged in successfully!" << endl;
					cout << "Welcome back " << user.UserID << "!" << endl;
					cout << endl;
					return 1;
				}
			}
		}
		return 0;

		//Close User.txt
		FileIn.close();
	}
	return 0;
}

void Register(REGISTER& new_user) //Register option chosen in Welcome()
{
	// Input user information
	cout << endl;
	char str[MaxID + 1];
	cout << "----------- REGISTER -----------" << endl;
	cout << "User ID: "; cin.ignore();  cin.getline(str, MaxID);
	new_user.id = str;
	_flushall();
	cout << "Password: "; cin.getline(str, MaxPass);
	new_user.pass = str;
	cout << "--------------------------------" << endl;

	// Write to User.txt
	ofstream FileOut;
	FileOut.open("User.txt", ios_base::app);
	FileOut << new_user.id << " ";
	FileOut << new_user.pass;
	FileOut << endl;
	FileOut.close();
}

int main()
{
	int Option, Choice; //Variable Option is for Welcome() function and the latter is for Menu() function
	int Check_Login; //Used to check if the user logged in

	LOGIN user; //already have an account
	REGISTER new_user; //make new account
	Car car; //add car

	Option = Welcome(Option);

	//Check Option
	if (Option == 1)
	{
		//Check Login
		Check_Login = Login(user);

		//Login successfully
		if (Check_Login == 1)
		{
			while (true)
			{
				system("pause");

				system("cls");
				Menu(Choice);
				{
					switch (Choice)
					{
					case 1: //Add car choice
					{
						system("color 02");
						Add(car);
						break;
					}
					case 2: //View car choice
					{
						system("color 07");
						View(car);
						break;
					}
					case 3: //Delete car choice
					{
						//Clear screen
						system("cls");
						system("color 0C");

						//Input plate number
						string plate;
						cout << endl;
						cout << "---------- DELETE CAR ----------" << endl;
						cout << "Plate Number: "; cin >> plate;
						cout << "--------------------------------" << endl;

						Delete(plate);
						break;
					}
					case 4: //Rent car choice
					{
						//Clear screen
						system("cls");
						system("color 0B");

						//Input plate number and days
						string plate; int days;
						//Assign user id
						string user_id = user.UserID;
						cout << endl;
						cout << "---------- CAR RENTAL ----------" << endl;
						cout << "Plate Number: "; cin >> plate;
						cout << "For how long? (days): "; cin >> days;
						cout << "--------------------------------" << endl;

						Rental(plate, user_id, days);
						break;
					}
					case 5: //Return car choice
					{
						//Clear screen
						system("cls");
						system("color 0E");

						//Input plate number
						string plate;
						//Assign user id
						string user_id = user.UserID;
						cout << endl;
						cout << "---------- RETURN CAR ----------" << endl;
						cout << "Plate Number: "; cin >> plate;
						cout << "--------------------------------" << endl;

						Return(plate, user_id);
						break;
					}
					case 6: //Exit choice
					{
						cout << "--- Thank you for choosing our service! ---";
						cout << endl;

						system("pause");
						return false;
						break;
					}
					default: //Invalid input
					{
						cout << "Please choose an option from 1 to 6. Please try again." << endl;
						break;
					}
					}

				}
			}
		}
		else //Wrong User ID or password
		{
			cout << "Can't login. Check your User ID or Password." << endl;

			system("pause");
			return 0;
		}
	}
	else if (Option == 2) //Create new account
	{
		Register(new_user);
		cout << endl;
		cout << "You now have an account. Login to use our services!" << endl;
		system("pause");
	} //Invalid input
	else cout << "Please enter 1 or 2. Try again!" << endl;

	system("pause");
	return 0;
}