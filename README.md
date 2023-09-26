# WhatsApp Water-Drinking Reminder

## Overview
This project is a customizable MFC application designed to remind users to drink water at user-specified intervals through WhatsApp messages. The user-friendly interface allows for easy adjustments of reminder intervals.

## Features
- Set up reminders with custom intervals.
- Receive reminders through WhatsApp messages.
- Customize message content.
- Start and Stop the reminders with a single click.
- Secure management of sensitive information using environmental variables.

## Setup and Installation
1. **Obtain API Key**
   - To get your API key, follow the instructions provided [here](https://www.callmebot.com/de/blog/kostenlos-api-whatsapp-nachrichten/).
   - After completing the API activation process, you will receive your API key, which will be used to send WhatsApp messages.
   
2. **Clone the Repository**
git clone https://github.com/junesjw/water-reminder-app.git

3. **Compile the Application**
- Open the project in Visual Studio.
- Build the project to produce the executable.

4. **Setup Environment Variables (Optional)**
Users need to set up the PHONE_NUMBER and API_KEY environment variables manually.
- For Windows, users can set up environment variables through System Properties -> Advanced -> Environment Variables.
- Users can verify the set environment variables using the command prompt with the commands:

```sh
echo %PHONE_NUMBER%
echo %API_KEY%
```

The fields will now be filled on application startup.

5. **Run the Application**
- Execute the application.
- Input the reminder interval and start the reminders.

## How to Use
1. **Start the Application**
- Run the executable to start the application.
- Input the reminder interval in the provided text box.

2. **Set the Interval**
- Enter the desired interval for the reminders (in milliseconds).
- Click the "Start" button to initiate the reminders.

3. **Receive Reminders**
- You will receive WhatsApp messages at the set intervals.
- Messages will continue until the application is closed or stopped.

## Security Considerations
Sensitive information such as phone numbers and API keys are securely managed using environmental variables. However, ensure the variables are properly secured and not easily accessible to unauthorized users.

## ToDo List
- ~~**Enhance User Interface:** Improve the aesthetics and user experience of the application's GUI.~~
- ~~**Customizable Messages:** Implement functionality allowing users to customize the content of reminder messages.~~
- **Specific Date/Time Reminders:** Extend the app to enable setting up reminders for specific dates and times.
- **Robust Error Handling:** Introduce more comprehensive error handling to manage potential issues and enhance application stability.
- **Server-Based Reminders on Linux:** Develop functionality to set up reminders that can run on a Linux server, eliminating the need for the application to be running in the background.
- ~~**Configuration through GUI:** Allow users to input API key and phone number directly through the application’s graphical interface, streamlining the setup process.~~

## License
This project is licensed under the MIT License.
