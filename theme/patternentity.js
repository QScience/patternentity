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
	$('#patternentity-search input#edit-search').autofill({
		value: 'search...',
		defaultTextColor: '#666',
		activeTextColor: '#333',
	});
	var value_input = $('#patternentity-search input').attr('value');
	var value_selected = $('#edit-selected option[selected="selected"]').attr('value');
	$("select#edit-selected").change(function () {
		var str = "";
		$("select#edit-selected option:selected").each(function () {
			var text_select = $(this).text();
			if (text_select == 'UUID') {
				$('#patternentity-search input#edit-search').autofill({
					value: 'e.g. 1f672fdf-24d2-64a4-e981-3d3f4cbe3d74',
					defaultTextColor: '#666',
					activeTextColor: '#333',
				});
			}
			else {
				$('#patternentity-search input#edit-search').autofill({
					value: 'search...',
					defaultTextColor: '#666',
					activeTextColor: '#333',
				});
			}
		});
	})

	//search box width.
	$('input#edit-search').css('width', '65%');

});
})(jQuery)
