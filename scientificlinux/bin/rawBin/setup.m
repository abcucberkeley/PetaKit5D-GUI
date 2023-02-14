function setup(codeRt, addPython, pythonPath)
% automatically load all code repositories to path
% 
% Author: Xiongtao Ruan
% Date: 10/05/2020


if nargin < 1 || isempty(codeRt)
    codeRt = fileparts(which(mfilename));
end

if nargin < 2
    addPython = false;
end

if nargin < 3 || isempty(pythonPath)
    pythonPath = '~/anaconda3/bin/python';
end

if ispc
    [~, output] = system('hostname');
else
    [~, output] = system('echo $HOSTNAME');
end
fprintf('Hostname: %s \n', strip(output))

fprintf('Add matlab libraries to path...\n')

addpath(genpath([codeRt, '/LLSM5DTools']));

% also add python libary
if addPython
    fprintf('Add python library to path...\n')
    try
        dir_info = dir(pythonPath);
        pe = pyenv;
        if ~contains(pe.Executable, 'miniconda3') && ~contains(pe.Executable, 'anaconda3') ...
                && ~strcmp(fileparts(pe.Executable), dir_info.folder)
            pyenv('Version', pythonPath);
        end
        

        pymod_rel_path = [codeRt, '/LLSM5DTools/microscopeDataProcessing/python/'];
        dir_info = dir(pymod_rel_path);
        pymod_path = dir_info.folder;
        insert(py.sys.path, int64(0), pymod_path);
        py.importlib.import_module('zarrAPI');
        py.importlib.import_module('daskAPI');
    catch ME
        disp(ME);
    end
end

end

