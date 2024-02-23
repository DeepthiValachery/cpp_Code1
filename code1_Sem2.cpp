/*	Student ID		:	[Redacted]
	Name			:	Deepthi Jibu Valachery
	Course code		:	COMP1602
	Assignment		:	1
*/

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

struct Date{															// Date struct
	int day;
	int month;
	int year;
};

Date getCurrentDate(){
    Date d;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    d.day   = aTime->tm_mday;
    d.month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    d.year  = aTime->tm_year + 1900;

    return d;
}

//write structure definitions here
struct Movies{
	int movieID;
	string name;
	string genre;
	int day;
	char s1;
	int month;
	char s2;
	int year;
	long long gross;
	float rate;
};

struct Actors{
	string ActorID;
	string fname;
	string lname;
	char gender;
	int age;
	string birthPlace;
};

struct Cast{
	int Mid;
	string Aid;
	string role;
};

//write print functions to print the details of each structure
void printMovies (Movies m){
	cout << "Movie ID: " <<  m.movieID<< endl;
	cout << "Movie Name: " << m.name << endl;
	cout << "Genre: " << m.genre << endl;
	cout << "Release Date: "<< m.day << m.s1 << m.month << m.s2 << m.year << endl;
	cout << "Grossings to Date: " << m.gross << endl;
	cout << "Ratings: " << m.rate << endl;
}

void printActors (Actors a){
	cout << "Actor ID: " << a.ActorID << endl;
	cout << "Full Name: " << a.fname << " " << a.lname << endl;
	cout << "Gender: " << a.gender << endl;
	cout << "Age: " << a.age << endl;
	cout << "Place of Birth: " << a.birthPlace << endl;
}

void printCast (Cast c){
	cout << "Movie ID: " << c.Mid << endl;
	cout << "Actor ID: " << c.Aid << endl;
	cout << "Actor's role in Movie: " << c.role << endl;
}

//This function reads the data from the file actors.txt and creates Actor structures and inserts them in an array of Actor structures.
//The function accepts the array of Actor structures and returns the number of elements in the array.
int loadActors(Actors actors[]) {
	ifstream inActor;
	inActor.open("Actors.txt");
	string ActorID;
	Actors a;
	
	if (!inActor.is_open()){
		cout << "Actor File is not open. Aborting..." << endl;
		return 0;
	}
	int numActors = 0;
	
	inActor >> ActorID;
	while (ActorID != "END"){
		a.ActorID = ActorID;
		inActor >> a.fname >> a.lname >> a.gender >> a.age >> a.birthPlace;
		
		actors[numActors] = a;
		numActors = numActors + 1;
		
		inActor >> ActorID;
	}
	inActor.close();
	return numActors;
}

//This function reads the data from the file movies.txt and creates Movie structures and inserts them in an array of Movie structures.
//The function accepts the array of Movie structures and returns the number of elements in the array.
int loadMovies (Movies movies[]) {
	ifstream inMovie;
	inMovie.open("movies.txt");
	int movieID;
	Movies m;
	
	if (!inMovie.is_open()){
		cout << "Movie File is not open. Aborting..." << endl;
		return 0;
	}
	int numMovie = 0;
	
	inMovie >> movieID;
	while (movieID != 0){
		m.movieID = movieID;
		inMovie >> m.name >> m.genre >> m.day >> m.s1 >> m.month >> m.s2 >> m.year >> m.gross >> m.rate;
		
		movies[numMovie] = m;
		numMovie = numMovie + 1;
		
		inMovie >> movieID;
	}
	inMovie.close();
	return numMovie;
}

//This function reads the data from the file cast.txt and creates Cast structures and inserts them in an array of Cast structures.
//The function accepts the array of Cast structures and returns the number of elements in the array.
int loadCast(Cast casts[]){
	ifstream inCast;
	inCast.open("cast.txt");
	int Mid;
	Cast c;
	
	if (!inCast.is_open()){
		cout << "Cast File is not open. Aborting..." << endl;
		return 0;
	}
	int numEntries = 0;
	
	inCast >> Mid;
	while (Mid != 0){
		c.Mid = Mid;
		inCast >> c.Aid >> c.role;
		
		casts[numEntries] = c;
		numEntries = numEntries + 1;
		
		inCast >> Mid;
	}
	inCast.close();
	return numEntries;
}

//This function searches the array of Actor structures for a given actor id. If the Actor with that actor id is found, the function returns the location in the array
//where the actor was found. If the actor is not found, the function returns -1.
int searchActorById(Actors actors[], int numActors, string actorId){
	for (int i=0;i<numActors;i++){
		if(actorId == actors[i].ActorID)
			return i;
	}
	return -1;
}


//This function searches the array of Actor structures for a given actor by their name. If the Actor with that name is found, the function returns the location in the array
//where the actor was found. If the actor is not found, the function returns -1.
int searchActorByName(Actors actors[], int numActors, string fName, string lName){
	for (int i=0;i<numActors;i++){
		if((fName == actors[i].fname) && (lName == actors[i].lname))
			return i;
	}
	return -1;
}


//This function searches the array of Movie structures for a given movie by their name. If the Movie with that name is found, the function returns the location in the array
//where the movie was found. If the movie is not found, the function returns -1.
int searchMovieByName(Movies movies[], int numMovies, string movieName){
	for (int i=0;i<numMovies;i++){
		if(movieName == movies[i].name)
			return i;
	}
	return -1;
}


//This function searches the array of Movie structures for a given movie id. If the Movie with that movie id is found, the function returns the location in the array
//where the movie was found. If the movie is not found, the function returns -1.
int searchMovieById(Movies movies[], int numMovies, int movieId){
	for (int i=0;i<numMovies;i++){
		if(movieId == movies[i].movieID)
			return i;
	}
	return -1;
}


// This functions searches for a movie. If the movie is found all of the information pertaining to the movie is printed.
// If it is not found an appropriate error message is printed.
void option1(Movies movies[], int numMovies, string movieName){
	cout << "You have chosen 1 (Movie Information)" << endl << endl;
	cout << "Enter the Movie Name: ";
	cin >> movieName;
	
	int movie = searchMovieByName(movies, numMovies, movieName);
	
	if (movie == -1){
		cout << "Error: " << movieName << " was not found." << endl << endl;
	}
	else{
		printMovies(movies[movie]);
		cout << endl;
	}
}

//This functions searches for a movie by name and prints the list of all the actors and the roles they played in the movie.
void option2(Movies movies[], int numMovies, string movieName, Actors actors[], int numActors, Cast casts[], int numEntries){
	cout << "You have chosen 2 (Movie Cast)" << endl << endl;
	cout << "Enter the Movie Name: ";
	cin >> movieName;
	
	int result1 = searchMovieByName(movies, numMovies, movieName);
	if (result1 == -1){
		cout << "Error: " << movieName << " was not found." << endl << endl;
		
	}else{
		int ID = movies[result1].movieID;
		for (int i=0;i<numEntries;i++){
			if (casts[i].Mid == ID){
				for (int j=0;j<numActors;j++){
					if (actors[j].ActorID == casts[i].Aid){
						cout << "Actor Name: " << actors[j].fname << " " << actors[j].lname << "\t";
						cout << "(" << casts[i].role << ")" << endl << endl;
					}
				}
			}
		}
	}
		
}


//This functions searches for an actor's name and list the name of the movie (s) and roles(s) played in the movie of all the movies the actor has acted
//in if the actor exists. If the actor exists but has not acted in any of the listed movies, display "Actor has not acted in any movie."
//If the actor does not exist, display an appropriate message.
void option4(Movies movies[], int numMovies, Actors actors[], int numActors, Cast casts[], int numEntries, string fName, string lName){
	cout << "You have chosen 4 (Actor Filmography)" << endl << endl;
	cout << "Enter actor name: " ;
	cin >> fName >> lName;
	
	int actor2 = searchActorByName(actors, numActors, fName, lName);
	
	if (actor2 == -1){
		cout << "Error: " << fName << " " << lName << " was not found." << endl << endl;
	}
	else{
		for (int i=0;i<numEntries;i++){
			if (casts[i].Aid == actors[actor2].ActorID){
				for (int j=0;j<numMovies;j++){
					if (movies[j].movieID == casts[i].Mid){
						cout << "Movie Name: " << movies[j].name << endl;
						cout << "Role in the movie: " << casts[i].role << endl << endl;
					}
				}
			}	
		}
	}
}

// This functions searches for an actor by name. If the actor is found all of the information pertaining to the actor is printed.
// If it is not found an appropriate error message is printed.
void option3 (Actors actors[], int numActors, string fName, string lName){
	cout << "You have chosen 3 (Actor Information)" << endl << endl;
	cout << "Enter the Actor Name: ";
	cin >> fName >> lName;
	
	int actor = searchActorByName(actors, numActors, fName, lName);
	
	if (actor == -1){
		cout << "Error: " << fName << " " << lName << " was not found." << endl << endl;
	}
	else{
		printActors(actors[actor]);
		cout << endl;
	}
}

//This function searches for and prints the names of all movies released within the last month.
void option5(Movies movies[], int numMovies){
	cout << "You have chosen 5 (Latest Releases)" << endl << endl;
	Date d=getCurrentDate();
	cout << "The Current Date is " << d.day << "/" << d.month << "/" << d.year << endl;
	cout << "Movies released within the last month." << endl << endl;
	for (int i=0;i<numMovies;i++){
		if ((movies[i].month=d.month-1) && (movies[i].year=d.year)){
			cout << movies[i].name << endl;
		}
	}
}


//This function searches for and prints the  name(s) of the movies and the release date of all the movies that have not been released yet.
void option6(Movies movies[], int numMovies){
	cout << "You have chosen 6 (Coming Soon)" << endl << endl;
	Date d=getCurrentDate();
	cout << "The Current Date is " << d.day << "/" << d.month << "/" << d.year << endl << endl;
	cout << "COMING SOON!" << endl << endl;
	for (int i=0;i<numMovies;i++){
		if ((movies[i].day>d.day) && (movies[i].month>=d.month) && (movies[i].year>=d.year)){
			cout << movies[i].name << endl;
		}
	}
}


//This function searches for and prints the names of all movies with a star rating of 8.0 or more that have grossed over 1 billion dollars.
void option7(Movies movies[], int numMovies){
	cout << "You have chosen 7 (Top-Rated Movies)" << endl << endl;
	cout << "Movies with 8.0 ratings and 1B grossings to date." << endl << endl;
	for (int i=0;i<numMovies;i++){
		if ((movies[i].rate>=8.0) && (movies[i].gross >= 1000000000)){
			cout << movies[i].name << endl;
		}
	}
}

//This function prints the menu options and prompts the user to enter a choice.
void printMenu() {
	cout << "\t\t\t MENU" << endl;	
	cout << "-----------------------------------------------------------"	<< endl;									
	cout << "1. Movie Information\t\t5. Latest Releases" << endl;
	cout << "2. Movie Cast\t\t\t6. Coming Soon" << endl;
	cout << "3. Actor Information\t\t7. Top-Rated Movies" << endl;
	cout << "4. Actor Filmography\t\t8. Exit" << endl << endl;
	cout << "Select a number: ";
};

int main(){
	Movies movies[100];												//arrays
	Cast casts[100];
	Actors actors[100];
	
	int numMovies = loadMovies(movies);								//giving value
	int numActors = loadActors(actors);
	int numEntries = loadCast(casts);
	
	int menu;														//variables
	string movieName, fName, lName;
	
	printMenu();
	cin >> menu;
	cout << "-----------------------------------------------------------"	<< endl;
	cout << endl;
	
	while(menu!=8){	

		if (menu==1){
			option1(movies, numMovies, movieName);	
		}
		else if (menu==2){
			option2(movies, numMovies, movieName, actors, numActors, casts, numEntries);
		}
		else if (menu==3){
			option3(actors, numActors, fName, lName);
		}
		else if (menu==4){
			option4(movies, numMovies, actors, numActors, casts, numEntries, fName, lName);
		}
		else if (menu==5){
			option5(movies, numMovies);
		}
		else if (menu==6){
			option6(movies, numMovies);
		}
		else if (menu==7){
			option7(movies, numMovies);
		}
		else if ((menu<1) || (menu>8)) {
			cout << "Invalid Option!" << endl;
		}
		printMenu();
		cin >> menu;
		cout << "-----------------------------------------------------------"	<< endl;
		cout << endl;
	}	
		
	return 0;
}
