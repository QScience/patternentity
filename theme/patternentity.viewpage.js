/**
 * @file 
 * patternentity view page js.
 *
 */
(function($){
$(document).ready(function() {

  $('#patternentity-page-pattern-field').hide();

  //popup in view page.
  $('#pattern_file_popup').click(function() {
    $('#patternentity-page-pattern-field').slideToggle('slow');
    return false;
  });


});
})(jQuery)
