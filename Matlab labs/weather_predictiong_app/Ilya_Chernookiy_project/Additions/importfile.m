function subset2020 = importfile(filename, dataLines)
%IMPORTFILE Import data from a text file
%  subset2020 = IMPORTFILE(FILENAME) reads data from text file FILENAME
%  for the default selection.  Returns the data as a table.
%
%  subset2020 = IMPORTFILE(FILE, DATALINES) reads data for the specified
%  row interval(s) of text file FILENAME. Specify DATALINES as a
%  positive scalar integer or a N-by-2 array of positive scalar integers
%  for dis-contiguous row intervals.
%% Input handling
% If dataLines is not specified, define defaults
if nargin < 2
    dataLines = [2, Inf];
end

%% Set up the Import Options and import the data
opts = delimitedTextImportOptions("NumVariables", 11);

% Specify range and delimiter
opts.DataLines = dataLines;
opts.Delimiter = ",";

% Specify column names and types
opts.VariableNames = ["STATE", "EVENT_TYPE", "BEGIN_DATE_TIME", "END_DATE_TIME", "DAMAGE_PROPERTY", "DAMAGE_CROPS", "BEGIN_LAT", "BEGIN_LON", "END_LAT", "END_LON", "EVENT_NARRATIVE"];
opts.VariableTypes = ["categorical", "categorical", "datetime", "datetime", "double", "double", "double", "double", "double", "double", "string"];

% Specify file level properties
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Specify variable properties
opts = setvaropts(opts, "EVENT_NARRATIVE", "WhitespaceRule", "preserve");
opts = setvaropts(opts, ["STATE", "EVENT_TYPE", "EVENT_NARRATIVE"], "EmptyFieldRule", "auto");
opts = setvaropts(opts, "BEGIN_DATE_TIME", "InputFormat", "dd-MMM-yy HH:mm:ss");
opts = setvaropts(opts, "END_DATE_TIME", "InputFormat", "dd-MMM-yy HH:mm:ss");
opts = setvaropts(opts, ["DAMAGE_PROPERTY", "DAMAGE_CROPS"], "TrimNonNumeric", true);
opts = setvaropts(opts, ["DAMAGE_PROPERTY", "DAMAGE_CROPS"], "ThousandsSeparator", ",");

% Import the data
subset2020 = readtable(filename, opts);

end