function mccMaster(functionName, varargin)
%#function setup
if strcmp('XR_microscopeAutomaticProcessing',functionName)
    XR_microscopeAutomaticProcessing_parser(varargin{1}, varargin{2:end});
elseif strcmp('XR_decon_data_wrapper',functionName)
    XR_decon_data_wrapper_parser(varargin{1}, varargin{2:end});
elseif strcmp('XR_crop_dataset',functionName)
    XR_crop_dataset_parser(varargin{1}, varargin{2}, varargin{3}, varargin{4:end})
elseif strcmp('XR_fftSpectrumComputingWrapper',functionName)
    XR_fftSpectrumComputingWrapper_parser(varargin{1}, varargin{2:end});
elseif strcmp('XR_FSC_analysis_wrapper',functionName)
    XR_FSC_analysis_wrapper_parser(varargin{1},varargin{2:end});
elseif strcmp('XR_MIP_wrapper',functionName)
    XR_MIP_wrapper_parser(varargin{1}, varargin{2:end});
elseif strcmp('XR_parallel_rsync_wrapper',functionName)
    XR_parallel_rsync_wrapper_parser(varargin{1}, varargin{2}, varargin{3:end});
elseif strcmp('simReconAutomaticProcessing',functionName)
    simReconAutomaticProcessing_parser(varargin{1}, varargin{2:end});
end

end