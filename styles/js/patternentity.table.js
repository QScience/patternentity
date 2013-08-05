/**
 * @file 
 * patternentity list table js.
 *
 */
(function($){
$(document).ready(function() {
	//when click on download link, download times grown by 1.
	var download_link = $(".pattern-entity-list-table .download-link");
	download_link.click(function() {
		var download_times = $(this).parent().prev().prev();
		var numb = Number(download_times.text()) + 1; 
		download_times.text(numb);
	});

	//voting link ajax.
  $('.pattern-entity-list-table a[class*="voting-link-"]').live('click', function () {

    var class_pid = $(this).attr('title');
    var link = $('.' + class_pid);
    $(link).each(function() {
      $(this).parent().children('.voting-link').addClass('voting-link-odd');
    });

    var url = $(this).attr('href');

    $.ajax({
      url: url,
      success: function(data) {
        var $score = $('#patternentity-page-pattern-description #pattern-entity-view-page-score', data);
        var $vote = $('#pattern-entity-view-page-vote', data);

        console.log($vote.text());
        var link_parent = $(link).parent();
        console.log(link_parent);
        $(link_parent).prev().prev().html($score.text());
        if ($vote.text() == 'voted'){
          $(link_parent).html($vote.wrap("<div></div>").parent().html());
          $(link_parent).children('.voted-sign').addClass('voting-link-odd');
        }
        else {
          $(link_parent).html($vote.wrap("<div></div>").parent().html());
        }
      }
    });
    return false;
  });
	//use moment.js to format upload time.
	$(".pattern-entity-list-table .upload-time").text(function(){
		return moment.unix($(this).attr("value")).fromNow();
	});

	//upload functionality ajax implementation
	$('.pattern-entity-list-table-wrap').first().prepend('<div id="patternentity-upload-form-js" class="hero-unit"></div>');
	var upload_form_div = $('#patternentity-upload-form-js');
	$(upload_form_div).hide();
	$('.upload-button-link').bind('click', function (){
		var url = $('.upload-button-link').attr('href');
		$.ajax({
			url: url,
			success: function(data) {
				if ( $(upload_form_div).is(':hidden')) {
					var upload_form = $('#patternentity-form', data).wrap("<div></div>").parent().html();
					$(upload_form_div).html(upload_form).slideDown('slow');
          Drupal.attachBehaviors($("#patternentity-form"));
				}
				else {
					$(upload_form_div).slideUp('slow');
				}
				//console.log(data.error);
				
			},
			error: function(jqXHR, exception) {
				//console.log(jqXHR.status);
				if (jqXHR.status == 403) {
					$(upload_form_div).slideUp('slow');
					$(upload_form_div).html('you don\'t have the permission to upload pattern files').slideDown('slow');
				}
			}
		});
    
		return false;
	});

	//only show upload link at the first table
	$('.pattern-entity-list-table-wrap .upload-button-link').not(':first').hide();
});
})(jQuery)
