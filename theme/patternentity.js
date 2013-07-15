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
		 //console.log(url);
		 $.ajax({
			url: url,
			success: function(data) {
				var $score = $('#patternentity-page-pattern-description #pattern-entity-view-page-score', data);
				var $vote = $('#patternentity-page-pattern-description #pattern-entity-view-page-vote', data);
				//console.log($score.text());
				//console.log($(link).text());
				var score_before = $(link).parent().prev().prev();
				//console.log($(score_before).text());
				//if ($score.text() == $(score_before).text()) {
        //  $(link).parent().html("voted");
				//}
				$(link).parent().prev().prev().html($score.text());
        $(link).parent().html($vote.html());
				console.log($vote.html());
			}
		});
		return false;
	});
});
})(jQuery)
