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
	  if ($(this).text() == 'show') {
		  $(this).text('hide');
	  }
	  else {
		  $(this).text('show');
	  }
    $('#patternentity-page-pattern-field').slideToggle('slow');
    return false;
  });


});
})(jQuery)
