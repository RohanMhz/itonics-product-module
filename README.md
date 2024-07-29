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

2. **Checkout the Feature Branch**
   - Switch to the `feat/rohan-product-module` branch to access the latest features and updates:
     ```bash
     git checkout feat/rohan-product-module
     ```

3. **Create `settings.php`**
   - Copy `sites/default/default.settings.php` to `sites/default/settings.php`.
   - Edit `settings.php` to configure your database connection and other settings as needed.

4. **(Optional) Set Up Docker Containers**
   - If you are using Docker, ensure Docker is installed and running.
   - Navigate to the project directory and start the Docker containers using:
     ```bash
     docker-compose up -d
     ```
   - If Docker does not work, you can opt for XAMPP as an alternative. 

5. **Run the Installation**
   - Open your project URL in a web browser to start the Drupal installation process.
   - Follow the on-screen instructions to complete the installation.

6. **Enable the Module**
   - Navigate to `Admin > Modules` in your Drupal admin interface.
   - Find the "Rohan Maharjan ITONICS Products", "Date", and "WYSIWYG" modules in the list and check the boxes next to them.
   - Click the "Save configuration" button at the bottom of the page.

7. **Configure the Module**
   - After enabling, go to `Admin > ITONICS > Products` to configure the module settings and manage your products.

## Usage
- Once the module is enabled, you can add new products, edit existing ones, and manage product listings through the provided interface.

## Support
For any issues or feature requests, please open an issue in the module's issue queue on the repository.

## License
This module is released under the [GNU General Public License](https://www.gnu.org/licenses/gpl-2.0.html).

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

## Acknowledgments
Thanks to the Drupal community for their support and resources.
