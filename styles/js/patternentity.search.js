(function($){
$(document).ready(function() {

	//autofill search box.
	function switch_autofill(text_select) {
		var value_autofill;
		switch (text_select) {
			case 'UUID': value_autofill = 'e.g. 1f672fdf-24d2-64a4-e981-3d3f4cbe3d74'; break;
			case 'Title': value_autofill = 'e.g. content,create,block,delete'; break;
			case 'Category': value_autofill = 'e.g. block,color,content,menu'; break;
			case 'Pid': value_autofill = 'e.g. 3 or any number'; break;
			case 'Author': value_autofill = 'e.g. Qscience'; break;
			case 'Tags': value_autofill = 'e.g. helloworld'; break;
			default: value_autofill = 'search...';
		}
		return value_autofill;
	}
	var value_input = $('#patternentity-search input#edit-search').val();
	var value_autofill = '';
	var value_default= '';
	var autofill_sign = false;
	if (value_input.length == 0 ) {
		var text_select = $("select#edit-selected option:selected").text();
		value_default = switch_autofill(text_select);
		$('#patternentity-search input#edit-search').autofill({
			value: value_default,
			defaultTextColor: '#666',
			activeTextColor: '#333',
		});
		autofill_sign = true;
	}
	$('#patternentity-search input#edit-search').blur(function() {
		var text_select = $("select#edit-selected option:selected").text();
		value_autofill = switch_autofill(text_select);
		value_input = $(this).val();
		if (value_input == value_default) {
			$(this).autofill({
				value: value_autofill,
				defaultTextColor: '#666',
				activeTextColor: '#333',
			});
			autofill_sign = true;
		}
		else {
			autofill_sign = false;
		}
	});
	$("select#edit-selected").change(function () {
		$("select#edit-selected option:selected").each(function () {
			if ( autofill_sign ) {
				var text_select = $(this).text();
				value_autofill = switch_autofill(text_select);
				$('#patternentity-search input#edit-search').autofill({
					value: value_autofill,
					defaultTextColor: '#666',
					activeTextColor: '#333',
				});
			}
		});
	})

	//search box width.
	$('input#edit-search').css('width', '65%');

  //search functionality ajax implementation
  $('#patternentity-search #edit-submit').live('click', function() {
    var table_wrap = $('.pattern-entity-list-table-wrap');

	var text_select = $("select#edit-selected option:selected").text();
	var value_default = switch_autofill(text_select);

    var search_text = $('#patternentity-search #edit-search').val().trim();
    if ( search_text == '' || search_text == value_default) {
      $(table_wrap).hide();
      $(table_wrap).first().html('To begin the search type something, e.g. "Block"').show('slow');
    }
    else {
      var search_type = $('#patternentity-search #edit-selected option:selected').val();
      var path = $(this).attr('name');
      path += search_type + '/' + search_text;
      console.log(encodeURI(path));

      //var table_wrap = $('.pattern-entity-list-table-wrap');

      $.ajax({
        url: path,
        success: function(data) {
          var table = $('.pattern-entity-list-table-wrap', data).html();
          if (table == null) {
            $(table_wrap).hide();
            $(table_wrap).first().text('nothing found.').show('slow');
          }
          else {
            $(table_wrap).hide();
            $(table_wrap).first().html(table).slideDown('slow');
            $(".pattern-entity-list-table .upload-time").text(function(){
              return moment.unix($(this).attr("value")).fromNow();
            });
			$('.pattern-entity-list-table-wrap').first().prepend('<div id="patternentity-upload-form-js" class="hero-unit"></div>');
			var upload_form_div = $('#patternentity-upload-form-js');
			$(upload_form_div).hide();
          }
        }
      });
    }
    return false;
  });


});
})(jQuery)
