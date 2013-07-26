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


	//upload functionality ajax implementation
	$('#patternentity-page-pattern-field').before('<div id="patternentity-upload-form-js" class="hero-unit"></div>');
	var upload_form_div = $('#patternentity-upload-form-js');
	$(upload_form_div).hide();
	$('.upload-button-link').live('click', function (){
		var url = $('.upload-button-link').attr('href');
		$.ajax({
			url: url,
			success: function(data) {
				if ( $(upload_form_div).is(':hidden')) {
					var upload_form = $('#patternentity-form', data).wrap("<div></div>").parent().html();
					$(upload_form_div).html(upload_form).slideDown('slow');
				}
				else {
					$(upload_form_div).slideUp('slow');
				}
				
			}
		});
		return false;
	});



});
})(jQuery)
