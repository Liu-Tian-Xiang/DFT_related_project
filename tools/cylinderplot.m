function cylinderplot(ch,loop,section)

    for k=0:section
    run(['./Out_',ch,num2str(loop),'_',num2str(k),'.m']);
    end

[n1, n2, n3] = size( ff );

r  = chebpts( n1 );
th = chebpts(n2);%[pi*trigpts( n2 ); pi];
z  = chebpts( n3 );

% Remove doubled-up data
%r  =  r(floor(n1/2)+1:end);
%th = th(floor(n2/2)+1:end);
%ff = ff(floor(n1/2)+1:end,:,:);
%ff(:,end+1,:) = ff(:,1,:);

[tt, rr, zz] = meshgrid(th, r, z);

% Slices in the cylinder to plot
rslice = rr([floor(n1/2)+1],1,1);
tslice = tt(1,[floor(n2/2)+1],1);
zslice = squeeze(zz(1,1,[floor(2*n3/5)+1 floor(3*n3/5)+1]));

hslicer = slice(tt,rr,zz,ff,tslice,rslice,zslice);
%hold on
%{
for j = 1:numel(hslicer)
    h = hslicer(j);
    [xs,ys,zs] = pol2cart(h.XData,h.YData,h.ZData);
    surf(xs,ys,zs,h.CData,'EdgeColor','none','FaceColor','Interp');
end
delete(hslicer)
axis([-1 1 -1 1 -1 1])
daspect([1 1 1])
hold off
%}
set(gca, 'Position', [0 0 1 1], 'CameraViewAngleMode', 'Manual')
colorbar('FontSize', 16, 'Position', [0.84 0.09 0.04 0.8])
axis off

end


