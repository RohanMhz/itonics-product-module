(function ($) {
    Drupal.behaviors.customBehavior = {
      attach: function (context, settings) {
        // Apply the behavior only once per element.
        $("#select-categories").multiSelect(); // Example usage.
      }
    };
  })(jQuery);