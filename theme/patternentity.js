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


  //var voting_link = jQuery(".pattern-entity-list-table .voting-link");
  //voting_link.click(function() {
  //  var pathname = window.location.pathname;
  //  window.location.replace(pathname);
  //});
});
