#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct for the base class Offer
typedef struct {
    int offerNumber;    // Unique offer number
    double price;       // Offer price
    char *location;     // Location
    char *country;      // Country
    int numDays;        // Number of days for the offer
} Offer;

// Function to initialize an offer
void InitOffer(Offer *offer) {
    offer->location = NULL;
    offer->country = NULL;
}

// Function to display an offer
void DisplayOffer(const Offer *offer) {
    printf("Offer Number: %d\n", offer->offerNumber);
    printf("Price: %.2f\n", offer->price);
    printf("Location: %s\n", offer->location);
    printf("Country: %s\n", offer->country);
    printf("Number of Days: %d\n", offer->numDays);
}

// Function to clean up memory allocated for an offer
void FreeOffer(Offer *offer) {
    free(offer->location);
    free(offer->country);
}

// Function to add an offer to the manager
void AddOffer(Offer *offer, double price, const char *location, const char *country, int numDays) {
    offer->offerNumber = 0;
    offer->price = price;
    offer->numDays = numDays;

    // Allocate memory for location and country and copy strings
    offer->location = strdup(location);
    offer->country = strdup(country);
}

// Struct for the derived class BeachVacation
typedef struct {
    Offer baseOffer;       // Base offer
    char sandType[100];    // Sand type
    int temperature;       // Temperature
} BeachVacation;

// Function to display a beach vacation offer
void DisplayBeachVacation(const BeachVacation *beachVacation) {
    DisplayOffer(&beachVacation->baseOffer);
    printf("Sand Type: %s\n", beachVacation->sandType);
    printf("Temperature: %d degrees Celsius\n", beachVacation->temperature);
}

// Function to clean up memory allocated for a beach vacation offer
void FreeBeachVacation(BeachVacation *beachVacation) {
    FreeOffer(&beachVacation->baseOffer);
}

// Struct for the derived class MountainVacation
typedef struct {
    Offer baseOffer;       // Base offer
    int altitude;          // Altitude
} MountainVacation;

// Function to display a mountain vacation offer
void DisplayMountainVacation(const MountainVacation *mountainVacation) {
    DisplayOffer(&mountainVacation->baseOffer);
    printf("Altitude: %d meters\n", mountainVacation->altitude);
}

// Function to clean up memory allocated for a mountain vacation offer
void FreeMountainVacation(MountainVacation *mountainVacation) {
    FreeOffer(&mountainVacation->baseOffer);
}

// Struct for managing offers
typedef struct {
    Offer *offers;        // Array for storing offers
    int currentOfferNumber; // Current number for offers
    int offerCount;       // Number of offers
} OfferManager;

// Function to initialize the offer manager
void InitOfferManager(OfferManager *manager) {
    manager->offers = NULL;
    manager->currentOfferNumber = 1;
    manager->offerCount = 0;
}

// Function to clean up memory allocated for offers
void FreeOffers(OfferManager *manager) {
    for (int i = 0; i < manager->offerCount; ++i) {
        FreeOffer(&manager->offers[i]);
    }
    free(manager->offers);
}

// Function to add an offer to the manager
void AddOfferToManager(OfferManager *manager, Offer *offer) {
    offer->offerNumber = manager->currentOfferNumber++;
    manager->offerCount++;
    manager->offers = (Offer *)realloc(manager->offers, manager->offerCount * sizeof(Offer));
    manager->offers[manager->offerCount - 1] = *offer;
}

// Function to display all offers
void DisplayAllOffers(const OfferManager *manager) {
    for (int i = 0; i < manager->offerCount; ++i) {
        DisplayOffer(&manager->offers[i]);
        printf("---------------------\n");
    }
}

// Function to display offers with a price lower than a given limit
void DisplayOffersBelowLimit(const OfferManager *manager, double priceLimit) {
    for (int i = 0; i < manager->offerCount; ++i) {
        if (manager->offers[i].price < priceLimit) {
            DisplayOffer(&manager->offers[i]);
            printf("---------------------\n");
        }
    }
}

// Function to delete an offer by its number
void DeleteOffer(OfferManager *manager, int offerNumber) {
    int index = -1;
    for (int i = 0; i < manager->offerCount; ++i) {
        if (manager->offers[i].offerNumber == offerNumber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        FreeOffer(&manager->offers[index]);

        for (int i = index; i < manager->offerCount - 1; ++i) {
            manager->offers[i] = manager->offers[i + 1];
        }
        manager->offerCount--;
        manager->offers = (Offer *)realloc(manager->offers, manager->offerCount * sizeof(Offer));
    }
}

// Main function
int main() {
    OfferManager manager;
    InitOfferManager(&manager);

    char continueAdding;
    do {
        printf("Select the type of offer (1 - Beach, 2 - Mountain): ");
        int offerType;
        scanf("%d", &offerType);

        double price;
        char location[100], country[100];

        printf("Enter the offer price: ");
        scanf("%lf", &price);

        printf("Enter the location: ");
        fflush(stdin);
        getchar(); // consume newline
        fgets(location, sizeof(location), stdin);
        location[strcspn(location, "\n")] = '\0'; // remove newline

        printf("Enter the country: ");
        fgets(country, sizeof(country), stdin);
        country[strcspn(country, "\n")] = '\0'; // remove newline

        int numDays;
        printf("Enter the number of days: ");
        scanf("%d", &numDays);

if (offerType == 1) {
    BeachVacation beachVacation;
    printf("Enter the sand type: ");
    fflush(stdin);
    getchar(); // consume newline
    fgets(beachVacation.sandType, sizeof(beachVacation.sandType), stdin);
    beachVacation.sandType[strcspn(beachVacation.sandType, "\n")] = '\0'; // remove newline

    printf("Enter the temperature: ");
    scanf("%d", &beachVacation.temperature);

    AddOffer(&beachVacation.baseOffer, price, location, country, numDays);
    AddOfferToManager(&manager, &beachVacation.baseOffer);
} else if (offerType == 2) {
            MountainVacation mountainVacation;
            printf("Enter the altitude: ");
            scanf("%d", &mountainVacation.altitude);

            AddOffer(&mountainVacation.baseOffer, price, location, country, numDays);
            AddOfferToManager(&manager, &mountainVacation.baseOffer);
        } else {
            printf("Invalid offer type.\n");
        }

        printf("Do you want to add another offer? (y = yes, n = no): ");
        scanf(" %c", &continueAdding);

    } while (tolower(continueAdding) == 'y');

    printf("\nAll offers:\n");
    DisplayAllOffers(&manager);

    double priceLimit;
    printf("\nEnter the price limit for display: ");
    scanf("%lf", &priceLimit);
    printf("\nOffers with a price lower than %.2f:\n", priceLimit);
    DisplayOffersBelowLimit(&manager, priceLimit);

    int offerToDelete;
    printf("\nEnter the offer number to delete: ");
    scanf("%d", &offerToDelete);
    DeleteOffer(&manager, offerToDelete);

    printf("\nOffers after deletion:\n");
    DisplayAllOffers(&manager);

    FreeOffers(&manager);

    return 0;
}
