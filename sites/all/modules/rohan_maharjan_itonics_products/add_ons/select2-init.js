
(function($) {
    Drupal.behaviors.textarea = {
        attach: function (context, settings) {
          $('.form-textarea-wrapper.resizable', context).once('textarea').each(function () {
            
          });
        }
      };
})(jQuery);