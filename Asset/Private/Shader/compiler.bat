set glslc = C:/VulkanSDK/1.2.176.1/Bin32/glslc.exe
set aa=.spv 
for %%i in (*.vert) do ( 
    glslc %%~fi -o %%i%aa%
)

for %%i in (*.frag) do ( 
    glslc %%~fi -o %%i%aa%
)