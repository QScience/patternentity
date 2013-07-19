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
	$('#pattern-entity-list-table-id .voting-link').live('click', function () {
		 var link = this;
		 var url = $(this).attr('href');
		 $.ajax({
			url: url,
			success: function(data) {
				var $score = $('#patternentity-page-pattern-description #pattern-entity-view-page-score', data);
				var $vote = $('#patternentity-page-pattern-description #pattern-entity-view-page-vote', data);
				var score_before = $(link).parent().prev().prev();
				$(link).parent().prev().prev().html($score.text());
				$(link).parent().html($vote.html());
			}
		});
		return false;
	});

	//autofill search box.
	//$('#patternentity-search #edit-search').attr('value');
	//autofill({
	//		value: 'search...',
	//		defaultTextColor: '#666',
	//		activeTextColor: '#333',
	//});
});
})(jQuery)
