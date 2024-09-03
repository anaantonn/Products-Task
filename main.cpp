#include <iostream>
#include <algorithm>
#include <cctype> // For toupper function
#include <map>

using namespace std;


class Product
{
public:
    string Name;
    float Price;
    string Type;

    Product(){}

    Product(string name, float price, string type)
    {
        Name = name;
        Price = price;
        Type = type;
    }
};


Product* productsinfo(Product* products, int begin, int end)
{
     for(int i = begin; i < end; i++)
    {
        cout << "Product " << i+1 << endl;

        Product p;
        cout << "Name: ";
        cin >> p.Name;

        cout << "Price: ";
        cin >> p.Price;

        cout << "Type: ";
        cin >> p.Type;

        products[i] = p;

    }
    return products;
}


bool compareByPrice(const Product& p1, const Product& p2)
{
    return p1.Price < p2.Price;
}

bool compareByType(const Product& p1, const Product& p2)
{
    return p1.Type < p2.Type;
}


// Function to convert a string to lowercase
string toLowercase(const string& str)
{
    string lower;
    for (char c : str)
    {
        lower += tolower(c);
    }
    return lower;
}


int startingMenu()
{
    int number;
    cout << "*** MENU ***" << endl;
    cout << "(1) Search for a certain product." << endl;
    cout << "(2) Sort products by price (ascending)." << endl;
    cout << "(3) Sort products by type (ascending)." << endl;
    cout << "(4) Calculate total price and amount for each type." << endl;
    cout << "(5) Quit!" << endl;
    cout << "Please enter your choice: ";
    cin >> number;
    return number;
}


int main()
{
    int size;
    cout << "Number of products to be added: ";
    cin >> size;

    Product* products = new Product[size]; // dynamic array to allow user input

    productsinfo(products,0,size);

    bool exit = false;
    for(;;)
    {
        int number = startingMenu();

        switch(number)
        {
        case 1:
            {

                string searchedProductName;
                cout << "Please enter the name of the product you are searching for: ";
                cin >> searchedProductName;

                bool found = false; // search through products case sensitive
                string lowerSearchedProductName = toLowercase(searchedProductName);
                for (int i = 0; i < size; i++)
                {
                    string lowerProductName = toLowercase(products[i].Name);
                    if (lowerSearchedProductName == lowerProductName)
                    {
                        cout << "Name: " << products[i].Name << ", Price: " << products[i].Price << ", Type: " << products[i].Type << endl;
                        found = true;
                        break; // No need to continue searching
                    }
                }

                if (!found)
                {
                    cout << "Product is not available! Please try again!" << endl;
                }
            }
            break;

        case 2:
            {
                sort(products, products+size, compareByPrice); // sorting all products by price

                cout << "Sorted products by price:\n";
                for (int i = 0; i < size; ++i)
                {
                    cout << "Name: " << products[i].Name << ", Price: " << products[i].Price << ", Type: " << products[i].Type << endl;
                }
            }
            break;

        case 3:

                 // Sort the products by type
            sort(products, products + size, compareByType);
            for (int i = 0; i < size; ++i)
                {
                    cout << "Name: " << products[i].Name << ", Price: " << products[i].Price << ", Type: " << products[i].Type << endl;
                }
            break;


        case 4:

            {
                    // Calculate total price for each type
                map<string, float> totalPriceByType;
                map<string, int> countByType;
                for (int i = 0; i < size; i++)
                {
                    totalPriceByType[products[i].Type] += products[i].Price;
                    countByType[products[i].Type]++;
                }

                // Print total price for each type
                cout << "Total price for each type:\n";
                for (const auto& pair : totalPriceByType)
                {
                    cout << "Type: " << pair.first << ", Total Price: " << pair.second << ", Count: " << countByType[pair.first] << endl;
                }
            }
            break;

        case 5:

                // Exit application
            exit = true;
            break;

        default:

            cout << "Please select again!" << endl;
            break;
        }

        if(exit)
            break;
    }

    delete[] products;

    return 0;
}
