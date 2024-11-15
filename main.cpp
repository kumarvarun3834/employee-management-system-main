#include <algorithm> // For transform
#include <chrono>    //for time manipulations
#include <cstdlib>   // For rand and srand
#include <ctime>     // For time (to seed rand)
#include <fstream>   // For file handling
#include <iomanip>   // for put_time
#include <iostream>  //basic library
#include <sstream>   //for string stream
#include <string>    //to store and manipulate the string
#include <vector>    //to store the data in list format 2D
#include <map>       //creating maps for data

using namespace std;

bool admin_user;
static string basedir = "Data/";
static string Datafile = basedir + "data.txt";
static string Attedata = basedir + "date_record/";
static string Attefile = Attedata + "attendance_history.txt";
static string assigned_work = basedir + "assigned_works/";
static string deleted_data = basedir + "deleted_data.txt";
static string status = basedir + "status.txt";

class filehandle
{
public:
  // this function is responsible to see that the file exits at that location or not
  bool fileExists(const std::string &filename)
  {
    std::ifstream file(filename);
    return file.good(); // Returns true if file exists, false otherwise
  }

  // this will modify all the readed lines from the file to an array
  vector<string> split(const string &str, char delimiter)
  {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter))
    {
      tokens.push_back(token);
    }
    return tokens;
  }

  // Function to read lines from a file and return them as a 2D vector by using split function
  vector<vector<string>> readLines(string file)
  {
    ifstream infile(file); // Open the file
    string line;
    vector<vector<string>> data; // 2D vector to store the CSV data

    // Check if the file is open
    if (!infile.is_open())
    {
      cout << "Error opening file." << endl;
      return data; // Return an empty 2D vector in case of error
    }

    // Read lines from the file
    while (getline(infile, line))
    {
      vector<string> result = split(line, ',');
      data.push_back(result); // Add the split line to the 2D vector
    }

    infile.close(); // Close the file
    return data;    // Return the 2D vector containing all lines
  }

  // Generalized function to save data into a file
  // 'data' is a string input separated by commas, 'file' is the file name
  void savedata_gen(string data, string file)
  {
    // Open file in append mode
    ofstream outputFile(file, ios::app);
    // it will check that the file is able to be opened or not
    if (!outputFile)
    {
      cout << "Error opening file for appending!" << endl;
      return; // Exit if file cannot be opened
    }

    if (!data.empty())
    {
      outputFile << data << endl; // Save data only if it's not empty
      cout << "YOUR GIVEN DATA IS SAVED" << endl;
    }
    cout << "Saving data to: " << file << endl;
    outputFile.close();
  }

  // generalize function for writing into the file from scratch and delete the existing data
  void writedata_gen(string data, string file)
  {
    // Open file in append mode
    ofstream outputFile(file);
    if (!outputFile)
    {
      cout << "Error opening file for appending!" << endl;
      return; // Exit if file cannot be opened
    }

    if (!data.empty())
    {
      outputFile << data << endl; // Save data only if it's not empty
    }
    cout << "Saving data to: " << file << endl;
    outputFile.close();
  }

  // this will handle the extraction part ie reading of specific data from database
  void get_data2(vector<string> &tokens)
  {
    cout << "empid:          | " << tokens[0] << endl
         << "username        | " << tokens[1] << endl
         << "Name:           | " << tokens[3] << endl
         << "position:       | " << tokens[4] << endl
         << "department:     | " << tokens[5] << endl
         << "age:            | " << tokens[7] << endl
         << "phoneno:        | " << tokens[8] << endl
         << "emergencyno:    | " << tokens[8] << endl
         << "email:          | " << tokens[10] << endl
         << "holidays:       | " << tokens[6] << endl
         << "salary:         | " << tokens[12] << endl
         << "joindate:       | " << tokens[11] << endl;
  }

  // this will autoreturn string of input vector
  string writing_general(vector<string> data)
  {
    string updatedData;
    for (int x = 0; x < data.size(); x++)
    {
      if (x == data.size() - 1)
      {
        updatedData += data[x] + "\n";
      }
      else
      {
        updatedData += data[x] + ",";
      }
    }
    cout << updatedData;
    return updatedData;
  }
};

class check
{

protected: // here I had declared all the constant functions and templates as
           // private that user don't have access to it directly
  string dept, name, email, position, joindate, phoneno, emergencyno;
  int empid, age;
  int salary, holidays;
  // most of these functions are predefined in doumentation of that header file
  // Function to get the current date
  string getCurrentDate()
  {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm *localTime = localtime(&currentTime);

    stringstream dateStream;
    dateStream << put_time(localTime, "%Y-%m-%d"); // Format: YYYY-MM-DD
    return dateStream.str();
  }

  // Function to get the current time
  string getCurrentTime()
  {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    tm *localTime = localtime(&currentTime);

    stringstream timeStream;
    timeStream << put_time(localTime, "%H:%M:%S"); // Format: HH:MM:SS
    return timeStream.str();
  }

  // this will check the validation of number ie 10 digit number
  bool valid_number(string x)
  {
    if (x.length() == 10)
    {
      cout << "Valid number" << endl;
      return true;
    }
    else
    {
      cout << x << endl;
      cout << "Not a valid number" << endl;
      return false;
    }
  }

  // this will check that email syntax is followed or not
  bool valid_email(const string &email)
  {
    // Find the position of '@' symbol
    size_t at_pos = email.find('@');

    // Check if '@' exists and is not at the start or end
    if (at_pos == string::npos || at_pos == 0 || at_pos == email.length() - 1)
    {
      cout << "Invalid email: missing or incorrectly placed '@'" << endl;
      return false;
    }

    // Find the position of the '.' symbol in the domain part (after '@')
    size_t dot_pos = email.find('.', at_pos);

    // Ensure there's at least one '.' in the domain part, and it's not at the end
    if (dot_pos == string::npos || dot_pos == email.length() - 1)
    {
      cout << "Invalid email: missing or incorrectly placed '.' in domain" << endl;
      return false;
    }

    cout << "Valid email" << endl;
    return true;
  }

  // this will check for validation of deparment
  bool valid_department(string dept)
  {
    // List of valid departments
    string valid_depts[] = {"HR", "IT", "Finance", "Marketing", "Operations", "Sales"};

    for (int i = 0; i < 6; i++)
    {
      if (dept == valid_depts[i])
      {
        return true; // Found a valid department
      }
    }

    return false; // No match found
  }

  // this will check for validation of position
  bool valid_position(string position)
  {
    // List of valid departments
    string valid_positions[] = {"Manager", "Assistant Manager",
                                "Clerk", "Accountant",
                                "Receptionist", "Sales Manager"};

    for (int i = 0; i < 6; i++)
    {
      if (position == valid_positions[i])
      {
        return true; // Found a valid department
      }
    }

    return false; // No match found
  }

  // this will check the year is leap or not
  bool is_leap_year(int year)
  {
    // Check if a year is a leap year
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  }

  // this will check the valid date of a perticular month
  bool valid_date(string date)
  {
    // Check if the date is in the correct format and valid
    if (date.length() != 8)
    {
      cout << "Invalid date format. It should be 8 digits long (DDMMYYYY)."
           << endl;
      return false;
    }

    // Extract day, month, and year from the string
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(2, 2));
    int year = stoi(date.substr(4, 4));

    // Check for valid month
    if (month < 1 || month > 12)
    {
      cout << "Invalid month. Must be between 1 and 12." << endl;
      return false;
    }

    // Check for valid day based on the month
    int max_days;
    switch (month)
    {
    case 2: // February
      max_days = is_leap_year(year) ? 29 : 28;
      break;
    case 4:
    case 6:
    case 9:
    case 11: // April, June, September, November
      max_days = 30;
      break;
    default: // Other months
      max_days = 31;
    }

    if (day < 1 || day > max_days)
    {
      cout << "Invalid day for the given month." << endl;
      return false;
    }

    // Check if year is within a reasonable range
    if (year < 1900 || year > 2100)
    {
      cout << "Invalid year. Must be between 1900 and 2100." << endl;
      return false;
    }

    // If all checks passed
    return true;
  }

  // this will check that the format of date is followed or not
  string check_date()
  {
    string date;
    cout << "Enter joining date (DDMMYYYY): " << endl;
    cin >> date;

    if (!valid_date(date))
    {
      cout << "Invalid date entered. Try again." << endl;
      return check_date(); // Retry until a valid date is entered
    }

    return date;
  }

  // // Function to generate random alphanumeric password
  string generate_password(int length)
  {
    string characters =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string password;

    for (int i = 0; i < length; i++)
    {
      password += characters[rand() % characters.length()];
    }

    return password;
  }

  // Function to extract username from email
  string generate_username(string email)
  {
    size_t pos = email.find('@');
    if (pos != string::npos)
    {
      return email.substr(0, pos);
    }
    return "";
  }

  // Validation for strings
  string checkstr(string word)
  {
    string input;
    char opt = 'n';

    // Loop until the user confirms the input
    while (opt != 'y')
    {
      cout << "Enter " << word << " of employee: " << endl;
      cin >> input;
      cout << "Check " << word << " --> " << input << endl;
      cout << "Is the entry correct? (y for yes, any other key to retry): ";
      cin >> opt;
      if (opt != 'y')
      {
        cout << "Retrying for " << word << "..." << endl;
      }
    }
    return input;
  }

  // Validation for integers
  int checkint(string word)
  {
    int input;
    char opt = 'n';

    // Loop until the user confirms the input
    while (opt != 'y')
    {
      cout << "Enter " << word << " of employee: " << endl;
      cin >> input;
      cout << "Check " << word << " --> " << input << endl;
      cout << "Is the entry correct? (y for yes, any other key to retry): ";
      cin >> opt;
      if (opt == 'y')
      {
        return input;
      }
      else
      {
        cout << "Retrying for " << word << "..." << endl;
      }
    }
    return 0;
  }

  // Similar while loop structure for phone number validation
  string check_phone_number()
  {
    string phone;
    while (true)
    {
      phone = checkstr("phone number");

      if (valid_number(phone))
      {
        return phone;
      }
      cout << "Invalid phone number. Please try again." << endl;
    }
  }

  // Validate email using a loop
  string check_email()
  {
    string email;
    while (true)
    {
      email = checkstr("email");
      if (valid_email(email))
      {
        return email;
      }
      cout << "Invalid email. Please try again." << endl;
    }
  }
};

class database_user : public check, public filehandle
{
  // created a class called database
  // in database all employee data will be stored
public:
  // Function to simulate a check-in process
  void check_in(vector<string> &tokens)
  {
    filehandle fh;                   // Assuming you're using the filehandle class for file operations
    string date = getCurrentDate();  // Get current date in your preferred format
    string time = getCurrentTime();  // Get current time in your preferred format
    string employeeName = tokens[1]; // Assuming tokens[1] contains the employee's name or username
    bool alreadyCheckedIn = false;

    // Check if today's attendance record exists
    if (!fh.fileExists(Attefile))
    {
      cout << "Creating attendance record for " << date << endl;
      fh.savedata_gen(date, Attefile); // Log the new attendance day in history
    }

    // Check if the employee has already checked in today
    if (fh.fileExists(Attedata + date + ".txt"))
    {
      auto temp = fh.readLines(Attedata + date + ".txt"); // Read the existing attendance data for today

      // Iterate through the list of check-ins for today
      for (int i = 0; i < temp.size(); i++)
      {
        if (temp[i][0] == employeeName)
        {
          // Employee already checked in
          alreadyCheckedIn = true;
          cout << "You have already checked in for today." << endl;
          break;
        }
      }
    }
    // If not checked in, save the check-in time
    if (!alreadyCheckedIn)
    {
      cout << "Checked in on " << date << " at " << time << endl;
      string data = employeeName + "," + time;
      fh.savedata_gen(data, Attedata + date + ".txt"); // Save the check-in data to the date's attendance file
    }

    cout << "Check-in process completed." << endl;
  }

  // for admin basic date choicemenu
  void show_attendance_history(vector<string> &tokens)
  {
    cout << "Displaying attendance history for employee ID: " << tokens[1]
         << endl;

    // Read attendance history from a file
    auto data = readLines(Attefile); // Assuming this reads lines from a file
    if (data.empty())
    {
      cout << "No attendance history found." << endl;
      return;
    }

    // Display attendance records
    for (int i = 0; i < data.size(); i++)
    {
      cout << i + 1 << ". " << data[i][0]
           << endl; // Display line number and data
    }

    // Get user choice
    int choice;
    cout << "Enter the number to view the specific attendance entry: ";
    cin >> choice;

    // Check if choice is valid
    if (choice >= 1 && choice <= data.size())
    {
      cout << "You selected: " << data[choice - 1][0] << endl;
    }
    else
    {
      cout << "Invalid choice, please enter a number between 1 and "
           << data.size() << endl;
    }
  }

  // Function to add leave for an employee
  void taken_leave(vector<string> &tokens)
  {
    int leaveDays;
    cout << "Enter the number of leave days to add: ";
    cin >> leaveDays;

    // Update leave days for the employee (assuming tokens[6] is the leave
    // count)
    int currentLeaves = stoi(tokens[6]);
    tokens[6] = to_string(currentLeaves - leaveDays);
    cout << "Total leaves remaining: " << tokens[6] << endl;
    string updatedData, record;
    // logic to update the file data
    auto data = readLines(Datafile);
    for (int i = 0; i < data.size(); i++)
    {
      if (data[i][1] == tokens[1])
      {
        data[i][6] = tokens[6];
        // break;
      }
      updatedData += writing_general(data[i]);
    }
    cout << "data updated" << endl;
    savedata_gen(updatedData, Datafile);
    record += tokens[1] + "," + tokens[3] + "," + tokens[4] + "," + tokens[5] + getCurrentDate() + "," + to_string(leaveDays) + "," + tokens[8] + "," + "\n";
    savedata_gen(record, Attefile);
  }

  // Function to show remaining leaves for the employee
  void show_remaining_leaves(vector<string> &tokens)
  {
    cout << "Remaining leaves for employee ID " << tokens[0] << ": "
         << tokens[6] << " days" << endl;
  }

  // this will handle the searching of users from databse
  int userfilter(vector<vector<string>> &data, bool task)
  {

    int i = 0;
    cout << data.size() << " is size of data it reads" << endl;
    while (i < data.size())
    {
      // cout<<"size of data : "<<data[i].size()<<endl;
      for (int x = 0; x < data[i].size(); x++)
      {
        if (x == data[i].size() - 1)
        {
          cout << " " << data[i][x] << endl;
        }
        else if (x == 0)
        {
          cout << i + 1 << " ";
        }
        else
        {
          // cout<<i<<" "<<x<<" ";
          cout << data[i][x] << " ";
        }
      }
      // cout << data[i][0] << " " << data[i][1] << " " << data[i][3] << " "
      //      << data[i][3] << " " << data[i][5] << " " << data[i][7] << endl;
      i++;
    }
    if (task)
    {
      int choice;
      cin >> choice;
      return choice;
    }
    return 0;
  }

  // this will show the profile of the user
  void employee_profile(vector<string> &tokens)
  {
    // Display employee profile details
    cout << "Displaying profile information..." << endl;
    // Future logic will go here
    get_data2(tokens);
  }

  // Function to get the rank of a position
  int getPositionRank(const string &position, const map<string, int> &position_rank_map)
  {
    auto it = position_rank_map.find(position); // Directly find the position without lowercase conversion
    if (it != position_rank_map.end())
    {
      return it->second; // Return the rank if found
    }
    return -1; // Return -1 if position is not in the map (invalid position)
  }

  // Comparator function to sort employees by position rank
  bool compareByRank(const vector<string> &emp1, const vector<string> &emp2, const map<string, int> &position_rank_map)
  {
    int rank1 = getPositionRank(emp1[4], position_rank_map); // emp1[4] is the position of the first employee
    int rank2 = getPositionRank(emp2[4], position_rank_map); // emp2[4] is the position of the second employee
    return rank1 > rank2;                                    // Sort in descending order (higher rank first)
  }

  // this will filter all the employee based on a perticular department
  vector<vector<string>> employeesfilter(vector<string> &tokens)
  {
    vector<vector<string>> filter;

    // Define a ranking system for the positions (higher number = higher position)
    map<string, int> position_rank_map = {
        {"Admin", 6},
        {"Manager", 5},
        {"Assistant Manager", 4},
        {"Sales Manager", 4},
        {"Accountant", 3},
        {"Clerk", 2},
        {"Receptionist", 1}};

    // Get the rank of the filtering position (tokens[4] holds the filtering position)
    int filter_rank = getPositionRank(tokens[4], position_rank_map);

    if (filter_rank == -1)
    {
      // If the filtering position is not valid, return an empty filter
      return filter;
    }

    // Read data from file
    auto data = readLines(Datafile);

    // Iterate through employee data
    for (int i = 0; i < data.size(); i++)
    {
      // Check if the token at index 5 matches the data at index 5 (adjust index as per your need)
      if (data[i][5] == tokens[5] && data[i][1] != tokens[1])
      {
        // Get the rank of the employee's position
        int employee_rank = getPositionRank(data[i][4], position_rank_map);

        // Include employee if their rank is less than or equal to the filter position rank
        if (employee_rank != -1 && employee_rank <= filter_rank)
        {
          filter.push_back(data[i]);
        }
      }
    }

    // Sort the filtered employees by their rank in descending order (higher positions first)
    sort(filter.begin(), filter.end(), [this, &position_rank_map](const vector<string> &emp1, const vector<string> &emp2)
         { return compareByRank(emp1, emp2, position_rank_map); });

    return filter;
  }

  // function responsible to show employee the work they are being assigned
  void displayAssignedWorks(vector<string> &tokens)
  {
    // filehandle fh;
    string employeeID = tokens[0]; // Assuming tokens[0] contains the employee's ID

    string filepath = assigned_work + tokens[1] + tokens[0] + ".txt";

    // Check if the file for assigned works exists
    if (fileExists(filepath))
    {
      cout << "No works have been assigned to this employee yet." << endl;
      return;
    }

    // Read the assigned works from the file
    vector<vector<string>> assignedWorks = readLines(filepath);

    if (assignedWorks.empty())
    {
      cout << "No works found for employee " << employeeID << endl;
      return;
    }

    // Display the works
    cout << "Assigned works for employee " << employeeID << ":" << endl;
    for (int i = 0; i < assignedWorks.size(); ++i)
    {
      cout << i + 1 << ". Work: " << assignedWorks[i][1] // Assuming 1st column is work
           << ", Deadline: " << assignedWorks[i][2]      // Assuming 2nd column is deadline
           << endl;
    }
  }

  // this line will show the list of all the workers under you
  // function responsible the employee to see the network how employee are connected to each other
  // here head can assign work to its co-workers and employee below them directly
  void displayWorkersAndCoworkers(vector<string> &filter)
  {
    // Display workers under the current employee and their coworkers
    cout << "Displaying workers under and co-workers.." << endl;
    // Future logic will go here
    auto data = employeesfilter(filter);
    int i = 0;
    cout << "listing co-workers :  " << endl;
    while (i < data.size())
    {

      cout << i + 1 << " " << data[i][1] << " " << data[i][4] << " "
           << data[i][3] << " " << data[i][5] << " " << data[i][7] << endl;
      i++;
    }
    return;
  }

  // Function to update the employee status
  // we made it text based so that even if user want to add any status so he can do so
  void setCurrentStatus(vector<string> &tokens)
  {
    string username = tokens[1]; // Assuming the first token is the username
    string newStatus;

    cout << "Enter your new status: ";
    cin.ignore();
    getline(cin, newStatus);

    vector<vector<string>> data = readLines(status);
    bool statusUpdated = false;
    string updatedData;

    // Iterate through existing data to update status
    for (auto &row : data)
    {
      if (row[0] == username)
      {
        row[1] = newStatus;
        statusUpdated = true;
      }
      updatedData += row[0] + "," + row[1] + "\n";
    }

    // If the username wasn't found, add a new entry
    if (!statusUpdated)
    {
      updatedData += username + "," + newStatus + "\n";
    }

    savedata_gen(updatedData, status);

    cout << "Status updated successfully!" << endl;
  }

  // this is search function of the employee list (used for selecton of employee)
  void searchlist(vector<string> &tokens)
  {
    displayWorkersAndCoworkers(tokens);
    int choice;
    auto data = employeesfilter(tokens);
    cout << "enter the number of employee to assign works to: ";
    cin >> choice;
    if (choice >= 1 && choice <= data.size())
    {
      cout << "you have selected : " << data[choice - 1][1] << endl;
      workassignbacklogic(stoi(data[choice - 1][0]));
    }
  }

  // assign work interface
  void assignWorks(vector<string> &tokens)
  {
    // Logic to assign works to other employees
    cout << "Assigning works..." << endl;
    auto filter = employeesfilter(tokens);
    // Future logic will go here
    while (true)
    {
      int choice;
      cout << "1. serch via employee ID" << endl;
      cout << "2. serch via username" << endl;
      cout << "3. serch via list" << endl;
      cout << "4. Exit" << endl;

      cout << "enter the way of your search" << endl;
      cin >> choice;

      switch (choice)
      {
      case 1:
      {
        int ID;
        cout << "enter the employee ID : ";
        cin >> ID;
        for (int i = 0; i < filter.size(); i++)
        {
          if (filter[i][0] == to_string(ID))
          {
            workassignbacklogic(ID);
          }
        }
        break;
      }
      case 2:
      {
        cout << "Enter the username of employee : ";
        string username;
        cin >> username;
        for (int i = 0; i < filter.size(); i++)
        {
          if (filter[i][1] == username)
          {
            string ID = filter[i][0];
            workassignbacklogic(stoi(ID));
          }
        }
        break;
      }
      case 3:
      {
        searchlist(tokens);
        break;
      }
      case 4:
      {
        return;
      }
      default:
      {
        cout << "choose a valid choice" << endl;
      }
      }
    }
  }

  // for user system input username and will display all info about it
  void view_employee_record(vector<string> &tokens)
  {
    auto dates = readLines(Attefile);
    cout << "displaying records for username: " << tokens[1] << endl;
    cout << "   date   " << "     time" << endl;
    for (int i = 0; i < dates.size(); i++)
    {
      vector<vector<string>> data = readLines(Attedata + dates[i][0] + ".txt");
      for (const auto &row : data)
      {
        if (row[0] == tokens[1])
        {
          cout << dates[i][0] << " - " << row[1] << endl;
          break;
        }
      }
    }
  }

  void delete_entry(vector<vector<string>> &tokens, int choice)
  {
    string db;

    // Iterate through tokens and build the new database content
    for (int i = 0; i < tokens.size(); i++)
    {
      if (i == choice - 1)
      {
        // Save deleted entry to "deleted_data" file
        savedata_gen(writing_general(tokens[i]), deleted_data);
        tokens.erase(tokens.begin() + i);
      }
      else
      {
        // Append the entry to the database string if it's not the deleted one
        db += writing_general(tokens[i]);
      }
    }

    // Write the updated database content back to Datafile file
    writedata_gen(db, Datafile);
    cout << "Entry deleted and database updated successfully." << endl;
  }

  // this is the logic for the work assigning to the employee ie writing to file
  void workassignbacklogic(int ID)
  {
    // logic to assign works back to the employee
    auto data = readLines(Datafile);
    cout << "enter the work you want to assign to the employee " << data[ID - 1][1] << endl;

    string work;
    cin >> work;
    cout << "deadline of task" << endl;
    string deadline = check_date();
    cout << "deadline: " << deadline << endl
         << "work    : " << work << endl;

    savedata_gen(to_string(ID - 1) + "," + work + "," + deadline, assigned_work + data[ID - 1][1] + to_string(ID - 1) + ".txt");
  }
};

class database_admin : public check, public filehandle
{
public:
  // Function to add a new employee
  // that there can be continuous data entry addition present in database
  void emp()
  {
    const string message =
        "type the number of entry you wanted to add in your database";
    cout << message << endl;

    int count = 0;

    cin >> count;
    cin.ignore();
    for (int i = 1; i <= count; i++)
    {
      setdata();
      get_data();
    };
  }

  void setdata()
  {
    email = check_email(); // Validated email input
    name = checkstr("name");
    joindate = check_date(); // Check for a valid date in DDMMYYYY format
    age = checkint("age");

    while (age < 18 || age > 59)
    {
      cout << "Invalid age. Age must be between 18 and 59." << endl;
      age = checkint("age");
    }

    phoneno = check_phone_number();     // Phone number validation
    emergencyno = check_phone_number(); // Emergency number validation

    dept = checkstr("department");
    while (!valid_department(dept))
    {
      cout << "Invalid department. Please try again." << endl;
      dept = checkstr("department");
    }

    position = checkstr("position");
    while (!valid_position(position))
    {
      cout << "Invalid position. Please try again." << endl;
      position = checkstr("position");
    }

    holidays = checkint("holidays");
    salary = checkint("salary");
  }

  // this command will handle all the data to append in the database as usual
  void savedata()
  {
    vector<vector<string>> datar = readLines(Datafile);
    vector<string> last = datar[datar.size()-1];
    string last_empid=last[0];
    empid = stoi(last_empid) + 1;
    // Seed random number generator for password generation
    srand(time(0));

    // Generate username and password
    string username = generate_username(email); // Generate username from email
    string password = generate_password(8);     // Generate random 8-character password

    string data = to_string(empid) + "," + username + "," + password + "," + name + "," + position + "," + dept + "," + to_string(holidays) + "," + to_string(age) + "," + phoneno + "," + emergencyno + "," + email + "," + joindate + "," + to_string(salary);

    cout << "\n\nUSERNAME: " << username << endl;
    cout << "PASSWORD: " << password << endl;
    cout
        << "username and passward is used for login purpose be sure to save it";
    // outputFile.close();
    savedata_gen(data, Datafile);
  }

  // this command will print the whole data given while addition and save them
  // to the text file automatically
  void get_data()
  {
    // cout << "empid" << "name" << "department" << "salary"<<endl;
    cout << "empid:          | " << empid << endl
         << "Name:           | " << name << endl
         << "department:     | " << dept << endl
         << "salary:         | " << salary << endl
         << "age:            | " << age << endl
         << "phoneno:        | " << phoneno << endl
         << "emergencyno:    | " << emergencyno << endl
         << "email:          | " << email << endl
         << "position:       | " << position << endl
         << "holidays:       | " << holidays << endl
         << "joindate:       | " << joindate << endl;
    cout << endl;

    savedata();
  }
};

class employee_interface : public database_user
{
public:
  void employee(vector<string> &tokens)
  {
    // 'tokens' holds employee data such as profile information
    if (admin_user)
    {
      cout << "Login successful! as username" << tokens[1] << endl;
      cout << "Displaying employee data..." << endl;
      cout << "Employee ID: " << tokens[0] << endl;
      cout << "Name: " << tokens[3] << endl;
      cout << "Position: " << tokens[4] << endl;
      cout << "Department: " << tokens[5] << endl;
      cout << "Age: " << tokens[7] << endl;
      cout << "Phone Number: " << tokens[8] << endl;
      cout << "Email: " << tokens[10] << endl;
      cout << "Join Date: " << tokens[11] << endl;
    }
    while (true)
    {
      admin_user = false;
      cout << "1. Profile" << endl;
      cout << "2. Assigned works" << endl;
      cout << "3. Assign works" << endl;
      cout << "4. Workers under you and co-workers" << endl;
      cout << "5. Set current status" << endl;
      cout << "6. Exit" << endl;

      int choice;
      cin >> choice;

      switch (choice)
      {
      case 1:
      {
        // Display employee profile information
        employee_profile(tokens);
        break;
      }
      case 2:
      {
        // Logic to show assigned works
        displayAssignedWorks(tokens);
        break;
      }
      case 3:
      {
        // Logic to assign works to other employees
        assignWorks(tokens);
        break;
      }
      case 4:
      {
        // Show workers under and coworkers
        displayWorkersAndCoworkers(tokens);
        break;
      }
      case 5:
      {
        // Update employee's current status
        setCurrentStatus(tokens);
        break;
      }
      case 6:
      {
        // Exit the loop
        cout << "Exiting employee system..." << endl;
        return;
      }
      default:
      {
        cout << "Invalid choice. Please try again." << endl;
        break;
      }
      }
    }
  }

  void employee_profile(vector<string> &tokens)
  {
    // here all employee system profile will be entered
    while (true)
    {
      cout << "1. check in" << endl;
      cout << "2. Attendence history" << endl;
      cout << "3. add leave" << endl;
      cout << "4. remaining leaves" << endl;
      cout << "5. employee details" << endl;
      cout << "6. Edit profile" << endl;
      cout << "0. exit" << endl;
      int choice;
      cin >> choice;
      switch (choice)
      {
      case 1:
      {
        check_in(tokens);
        break;
      }
      case 2:
      {
        view_employee_record(tokens);
        break;
      }
      case 3:
      {
        taken_leave(tokens);
        break;
      }
      case 4:
      {
        show_remaining_leaves(tokens);
        break;
      }
      case 5:
      {
        get_data2(tokens);
        break;
      }
      case 6:
      {
        // edit profile logic
        cout << "what you want to edit" << endl;
        get_data2(tokens);
        break;
      }
      case 0:
      {
        cout << "entering back to main menu" << endl;
        return;
      }
      default:
      {
        cout << "PLEASE SELECT VALID OPTION" << endl;
        break;
      }
      }
    }
  }
};

class admin_interface : public employee_interface, public database_admin
{
public:
  // this will display record of users
  int acess_user(vector<vector<string>> &data)
  {
    // this function is responsible for reading data from database and give user choice to choose make it
    cout << "select the user of which data you want to update" << endl;
    cout << "list all entries" << endl;
    int cho = userfilter(data, true);
    return cho;
  }

  int admin()
  {
    while (true)
    {
      vector<vector<string>> data = database_admin::readLines(Datafile);
      cout << "Size of database current : " << data.size() << endl;
      admin_user = true;
      cout << "enter the number of operation you want to perform" << endl;
      cout << "1. add new entry" << endl;
      cout << "2. list all entries" << endl;
      cout << "3. login as a user" << endl;
      cout << "4. delete an entry" << endl;
      cout << "5. search an entry" << endl;
      cout << "6. log out" << endl;
      int choice;
      cin >> choice;
      switch (choice)
      {
      case 1:
      {
        cout << "add new entry" << endl;
        emp();
        break;
      }
      case 2:
      {
        cout << endl;
        cout << "list all entries" << endl;
        userfilter(data, false);
        cout << endl;
        break;
      }
      case 3:
      {
        // Implement update functionality
        cout << "login as a user" << endl;
        employee(data[acess_user(data) - 1]);
        break;
      }
      case 4:
      {
        // Implement delete functionality
        cout << "delete an entry" << endl;
        delete_entry(data, acess_user(data));
        break;
      }
      case 5:
      {
        // Implement search functionality
        cout << "search an entry" << endl;
        break;
      }
      case 6:
      {
        cout << "Exiting program..." << endl;
        return 0; // Exit the program
      }
      default:
      {
        cout << "Invalid choice. Please try again." << endl;
      }
      }
    }
  }
};

class loginsys : private admin_interface
{
public:
  // this handles the login of user
  void login(string &username, string &password)
  {

    // we are reading data again and again so that if data is updated later on via another instance during expantion of system like adding multiple instances of users login
    // note we didn't worked on multiple instances of login till yet but made in such a way so that if there is that sort of thing occur then it will be easier to do so
    auto data = database_admin::readLines(Datafile);
    // this below for loop is used to treverse the whole array so that data after reading the database for login
    for (int i; i > data.size(); i++)
    {
      // Assign values to variables
      string emp_username = data[i][1];
      string emp_password = data[i][2];

      // Verify the credentials
      if (emp_username == username && emp_password == password)
      {
        cout << "Login successful!" << endl;
        cout << "Displaying employee data..." << endl;
        cout << "Employee ID: " << data[i][0] << endl;
        cout << "Name: " << data[i][3] << endl;
        cout << "Position: " << data[i][4] << endl;
        cout << "Department: " << data[i][5] << endl;
        cout << "Age: " << data[i][7] << endl;
        cout << "Phone Number: " << data[i][8] << endl;
        cout << "Email: " << data[i][10] << endl;
        cout << "Join Date: " << data[i][11] << endl;
        employee(data[i]);
        break;
      }
      else if (i == data.size())
      {
        cout << "invalid credentials try again" << endl;
      }
    }
    return;
  }

  // this is the main entry page of that program ie login page
  void start()
  {
    string username, password;
    // here while loop is used so that if user types the wrong id password then it will just runned until system is running
    while (true)
    {
      cout << "    WELCOME    " << endl;
      cout << "LOG IN INTO YOUR ACCOUNT" << endl;
      cout << "enter username" << endl;
      cin >> username;
      cout << "enter password" << endl;
      cin >> password;

      if (username == "admin" && password == "royalbee")
      {
        cout << "Login successful!" << endl;
        // here below function will give admin area login succesfully
        admin();
        return;
      }
      else
      {
        // here the below function is responsible for users login
        login(username, password);
      }
    }
  }
};

int main()
{
  // this is the main driver code where the object for isolated login system is called
  loginsys a;
  a.start();
  return 0;
};
