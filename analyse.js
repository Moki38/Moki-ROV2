console.log(process.argv[2]);

var winston = require('winston');
var logfile_name = './log/'+ process.argv[2];
  var logger = new (winston.Logger)({
    transports: [
      new (winston.transports.File)({
        filename: logfile_name,
        json: true,
        stringify: (obj) => JSON.stringify(obj),
      })
    ]
  });

 var options = {
    from: new Date - 24 * 60 * 60 * 1000,
    until: new Date,
    limit: 0,
    start: 0,
    order: 'desc',
    fields: ['Hover','Pilot','X','Y','Z','event']
  };

  //
  // Find items logged between today and yesterday.
  //
//  winston.query(options, function (err, results) {
  logger.query(options , function (err, results) {
    if (err) {
      throw err;
    }
    console.log(results);
  });



