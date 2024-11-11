# employee management system main

This C++ program is designed for managing employee information, tasks, attendance, and more, offering interfaces for both employees and administrators. The system allows user authentication, detailed profile management, and employee supervision. It is structured to be extensible, making it easy to add new features, such as admin account management.

### Project Structure

1. **Employee Interface**:
   - Allows employees to view and update their profiles, manage tasks, and track attendance.
   - **Key Features**:
     - **Profile Display**: Employees can view their personal details such as name, position, department, and contact information.
     - **Task Management**: Employees can view assigned tasks and assign tasks to others (coming soon).
     - **Attendance Tracking**: Employees can check in, view attendance history, and manage leave requests.
     - **Set Work Status**: Employees can update their current work status (coming soon).

2. **Admin Interface**:
   - Grants administrators full control over employee data and access to system management.
   - **Key Features**:
     - **Add New Employees**: Admins can create new employee records.
     - **List All Employees**: Admins can view a list of all employees; the list feature is complete, while the search functionality will be added soon.
     - **Manage Admin Accounts** (coming soon): Admins will soon be able to add and manage additional admin accounts.
     - **Employee Profile Access**: Admins can temporarily log in as an employee to view and update their profile.

3. **Login System**:
   - Acts as the system entry point, handling authentication for both employees and administrators.
   - **Admin Login**:
     - Admin access uses a default account (`username: admin`, `password: royalbee`) to access the admin interface.
   - **Employee Login**:
     - Standard employees log in with their individual credentials to view and update their profiles.

### Extensible Design

This system is structured for easy expansion to include new features without major code changes. Planned future updates include:

- **Admin Management**: Adding capabilities for admins to manage other admin accounts.
- **Employee Search**: Expanding the search function to allow filtering by criteria such as department or position.
- **Task Delegation**: Adding detailed task management for assigning tasks and tracking their completion.

### How to Run This Code

1. **Compile**: Use a C++ compiler, such as `g++`, to compile the program. In the command line, navigate to the directory containing the source files and enter:
   ```bash
   g++ main.cpp -o employee_management_system
   ```
   
2. **Run**: Execute the compiled program by entering:
   ```bash
   ./employee_management_system
   ```
   
3. **Login**:
   - On launch, the program will prompt for a username and password.
   - For admin access, enter the default credentials (`username: admin`, `password: royalbee`).
   - For employee access, use assigned credentials.
   
4. **Navigate**: Follow the on-screen menu options to perform tasks like viewing profiles, managing tasks, and tracking attendance.

This README provides an overview of the current functionality, along with instructions to run the code, highlighting the modular structure to ensure easy future enhancements.