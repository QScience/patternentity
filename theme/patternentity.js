/**
 * @file 
 * patternentity list table js.
 *
 */
jQuery(document).ready(function() {
  //when click on download link, download times grown by 1.
  var download_link = jQuery(".pattern-entity-list-table .download-link");
  download_link.click(function() {
      var download_times = jQuery(this).parent().prev().prev();
      var numb = Number(download_times.text()) + 1; 
      download_times.text(numb);
  });

  //var url_div = window.location.href;
  //url_div += "#pattern-entity-list-table-id";
  //alert(url_div);

  //var voting_link = jQuery(".pattern-entity-list-table .voting-link");
  //voting_link.click(function() {
  //    //var url_div = jQuery(this).attr("href");
  //    //url_div += "#content";
  //    //alert(url_div);
  //    jQuery(document).load(url_div);
  //    return false;
  //});
});
