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
	$('#pattern-entity-list-table-id .voting-link').click(function () {
		 var link = this;
		 var url = $(this).attr('href');
		 //console.log(url);
		 $.ajax({
			url: url,
			success: function(data) {
				var $score = $('#patternentity-page-pattern-description dl dd:last', data);
				//console.log($score.text());
				//console.log($(link).text());

				$(link).parent().prev().prev().html($score.text());
				//console.log(this);
			}
		});
		return false;
	});
});
})(jQuery)
