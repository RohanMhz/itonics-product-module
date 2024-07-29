# Rohan Maharjan ITONICS Products

## Overview
The Rohan Maharjan ITONICS Products module is a custom module designed to manage ITONICS products within your Drupal site. This module provides an interface for adding, editing, and displaying products.

## Requirements
- Drupal 7.x
- PHP 5.6 or higher
- MySQL 5.5 or higher (or equivalent)

## Installation

1. **Clone the Repository**
   - Clone the repository containing the Drupal project and module using:
     ```bash
     git clone https://github.com/RohanMhz/itonics-product-module.git
     ```

2. **Create `settings.php`**
   - Copy `sites/default/default.settings.php` to `sites/default/settings.php`.
   - Edit `settings.php` to configure your database connection and other settings as needed.

3. **(Optional) Set Up Docker Containers**
   - If you are using Docker, ensure Docker is installed and running.
   - Navigate to the project directory and start the Docker containers using:
     ```bash
     docker-compose up -d
     ```
   - If Docker does not work, you can opt for XAMPP as an alternative. 

4. **Run the Installation**
   - Open your project URL in a web browser to start the Drupal installation process.
   - Follow the on-screen instructions to complete the installation.

5. **Enable the Module**
   - Navigate to `Admin > Modules` in your Drupal admin interface.
   - Find the "Rohan Maharjan ITONICS Products", "Date", and "WYSIWYG" modules in the list and check the boxes next to them.
   - Click the "Save configuration" button at the bottom of the page.

6. **Configure the Module**
   - After enabling, go to `Admin > ITONICS > Products` to configure the module settings and manage your products.

## Usage
- Once the module is enabled, you can add new products, edit existing ones, and manage product listings through the provided interface.

## Support
For any issues or feature requests, please open an issue in the module's issue queue on the repository.
